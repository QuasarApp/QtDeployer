import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Item {

    id: ab
    signal exit
    property string type: qsTr("About")
    Rectangle {
        color: "#eee"
        anchors.fill: parent
    }
    Image {
        x: 0
        y: 0
        width: parent.width
        height: parent.height * 0.2
        fillMode: Image.PreserveAspectFit
        source: "/icon"
    }
    Label {
        id: txt
        x: parent.width * 0.1
        y: parent.height * 0.3
        width: parent.width * 0.8
        height: parent.height * 0.6
        font.pixelSize: (ab.width < ab.height) ? ab.width / 30 : ab.height / 30
        wrapMode: Text.Wrap
        text: qsTr("This application forked by ShahriarSS
Page of original soft: https://github.com/ShahriarSS/QtLinuxDeployer

version: "+MainManager.appVer()+"

Developers of fork:
* Programmer: Yankovich Andrei.
* Designer: Bakovets Alina.

 This application is distributed under the LGPLv3 license.

 Contact: https://github.com/EndrII
 Copyright (C) 12 Mar 2018 - Apr 10, 2018  ShahriarSS.
 Copyright (C) Apr 10, 2018 QuasarApp.")
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            swipeview.currentIndex = 0
        }
    }
}
