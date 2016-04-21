#include "mycam.h"
#include <chrono>
using namespace std::chrono;

high_resolution_clock::time_point global_time;
float global_frame;

MyCam::MyCam(QObject *parent) : QObject(parent)
{
  global_time = high_resolution_clock::now();
  global_frame = 30.0;
 /* qDebug() << "MY CAMERA INITIAL ============================================================= " ;
  cam_buff_ = new CamFrameBuffer(this);
  //camera_ = new QCamera(this);
  video_probe_ = new QVideoProbe();

  this->setViewfinder(cam_buff_);
  connect(cam_buff_, SIGNAL(frameAvailable(QImage)), this, SLOT(frameHandle(QImage)));

  qDebug() << "buffer is set  =============================================================" ;


  if (video_probe_->setSource(this))
  {
    connect(video_probe_, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(frameHandle(QVideoFrame)));
    qDebug() << "probe is set  =============================================================" ;
  }
  else
  {
    this->setViewfinder(cam_buff_);
    connect(cam_buff_, SIGNAL(frameAvailable(QImage)), this, SLOT(frameHandle(QImage)));
    qDebug() << "buffer is set  =============================================================" ;
    //this->start();
  }
  this->start();*/
}

void BGR32toMat(QVideoFrame *video_frame, cv::Mat *mat_img, int mat_channel)
{
  video_frame->map(QAbstractPlanarVideoBuffer::ReadOnly);
  QSize frame_size = video_frame->size();

  uchar *frame_bits = video_frame->bits();
  //uchar *img_bits = q_image.bits();

  int frame_width = frame_size.width();
  int frame_height = frame_size.height();

  mat_img = new cv::Mat(frame_height, frame_width, mat_channel);
  // cv::Mat mat_image(frame_height, frame_width, mat_channel);
  //uchar *mat_bits = mat_img.data;
  int count_f = 0;
  int count_m = 0;

  for (int y = 0; y < frame_height; y++)
  {
    for (int x = 0; x < frame_width; x++)
    {

      *(mat_img->data + count_m) = *(frame_bits + count_f);
      *(mat_img->data + count_m + 1) = *(frame_bits + count_f + 1);
      *(mat_img->data + count_m + 2) = *(frame_bits + count_f + 2);

     // uchar b = *(frame_bits + count_f);
     // uchar g = *(frame_bits + count_f + 1);
     // uchar r = *(frame_bits + count_f + 2);

      //cv::Vec3b pixel(b, g, r);
      //mat_image.at<cv::Vec3b>(y, x) = pixel;

      count_f += 4; // RGB32 0xbbggrrFF Skip the 0xFF
      count_m += 3;
    }

  }

  //mat_img = mat_image;
  video_frame->unmap();

}



void MyCam::frameHandle(const QVideoFrame &frame)
{
  high_resolution_clock::time_point t2;
  // qDebug() << "Heres a new Frame as QVideoFrame";

  QVideoFrame cloneFrame(frame);

  if( cloneFrame.pixelFormat() == QVideoFrame::Format_BGR32)
  {
    qDebug() << "Mat Image =====================================================================";
    cv::Mat *image;
    BGR32toMat(&cloneFrame, image, CV_8UC3);
    emit frameChanged(*image);
    //cv::imshow("thisWorks", *image);
  }
  else
  {
    //cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //qDebug() << " Frame is Valid " ;
    //const QImage image(cloneFrame.bits(),cloneFrame.width(), cloneFrame.height(), QVideoFrame::imageFormatFromPixelFormat(cloneFrame .pixelFormat()));

    //auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    //qDebug() << " microseconds - " << duration;
    //float frame_rate = 1000.0 / (float(duration) / 1000.0);
    //qDebug() << " FPS - " << frame_rate;
    //cloneFrame.unmap();
    //emit frameChanged(image);
  }

  t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - global_time ).count();
  float frame_rate = 1000.0 / (duration / 1000.0);
  qDebug() << " FPS - " << frame_rate;

  global_frame = (global_frame + frame_rate ) / 2.0;
  qDebug() << " Average FPS - " << global_frame;

  global_time = high_resolution_clock::now();
}


/*
{
  qDebug() << " HANDLE FRAME  =============================================================";
  if (video_frame.isValid())
  {
    qDebug() <<  "frame is Valid ";
  }
}*/
/*
void MyCam::frameHandle(QImage frame)
{
 qDebug() << "Heres a new Frame as QImage";
 //frame.save("Works", "PNG");

 emit frameChanged(frame);

}
*/

void MyCam::setCameraSource(QObject *value)
{
  QVariant mediaObject = value->property("mediaObject");

  qDebug() << "Camera source ";
  qDebug() <<"MediaObject set " ;
    if(mediaObject.isValid())
    {
     qDebug() << "MediaObject Valid ";
      camera_ = mediaObject.value<QCamera*>();

      if(camera_ && camera_->availability() == QMultimedia::Available)
      {
        qDebug() << "Camera availibe ";
        video_probe_ = new QVideoProbe(this);

        if (video_probe_->setSource(camera_))
        {
          connect(video_probe_, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(frameHandle(QVideoFrame)));
          qDebug() << "VideoProbe and SIGNALS are set get ready for the QImage frames " ;
        }

      }
      else
        qDebug() << "Camera unavalible ";
    }

}


void MyCam::startCam()
{
  camera_->start();
}

void MyCam::stopCam()
{
  camera_->stop();
}
