#ifndef MYCAM_H
#define MYCAM_H

#include <QObject>
#include <QCamera>
#include <QVideoProbe>
#include <QDebug>

#include <opencv/highgui.h>
#include <opencv/cv.hpp>
#include <iostream>

class MyCam : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *source READ source WRITE setCameraSource )
    Q_PROPERTY(QImage frame READ frame NOTIFY frameChanged)

  public:
    explicit MyCam(QObject *parent = 0);

    Q_INVOKABLE QImage frame() { return image_frame_; }
    Q_INVOKABLE QObject* source() {return this;}

  signals:
    void frameChanged(QImage);
    void frameChanged(cv::Mat);


  public slots:

    Q_INVOKABLE  QObject* getCameraSource() {return this;}

    void setCameraSource(QObject *value);

    void frameHandle(const QVideoFrame &frame);
    /*
    void frameHandle(QImage);
    */
    void startCam();
    void stopCam();

  private:
    QCamera *camera_;
    QVideoProbe *video_probe_;
    QVideoFrame *video_frame_;
    QImage image_frame_;


};

#endif // MYCAM_H
