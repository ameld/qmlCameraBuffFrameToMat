import QtQuick 2.6

import QtMultimedia 5.5
import QtQuick.Controls 1.5


import uri.cam 1.0


ApplicationWindow {
  height: 500
  width: 600
  visible: true

  menuBar: MenuBar {
      Menu {
          title: qsTr("File")
          MenuItem {
              text: qsTr("&Open")
              onTriggered: console.log("Open action triggered");
          }
          MenuItem {
              text: qsTr("Exit")
              onTriggered: Qt.quit();
          }
      }
  }

  Camera{
    id: camera

  }

  MyCam{
    id: my_cam
    source: camera

  }

  VideoOutput{
    fillMode: Image.PreserveAspectCrop
    source: camera
    //anchors.fill: parent
    autoOrientation: true
  }
}
