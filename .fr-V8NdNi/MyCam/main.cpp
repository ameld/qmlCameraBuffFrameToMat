#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "mycam.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);


  qmlRegisterType<MyCam>("uri.cam",1 ,0, "MyCam");
  QQmlApplicationEngine engine;
 // MyCam camera;
 // camera.stopCam();

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
 // camera.startCam();
  return app.exec();
}
