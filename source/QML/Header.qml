import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

TopBar {
    property string message: "Qt Deployer"
        text: message

        ToolButton {
            id: home
            text: "➔"
            rotation: 180
            font.pointSize: largeFont
            anchors.right: parent.right
            onClicked: swipeview.currentIndex = 0
            anchors.verticalCenter: parent.verticalCenter
        }
        ToolButton {
            text: qsTr("About")
            font.pointSize: smallFont
            anchors.right: home.left
            onClicked: {
                swipeview.currentIndex = 4
            }
            anchors.verticalCenter: parent.verticalCenter
        }
    }
