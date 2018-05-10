import QtQuick 2.7
import Qt.labs.platform 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
	id: window
	visible: true
    title: qsTr("Qt Deployer")

	width: 600
	height: sp.implicitHeight + 30

	property real smallFont: window.font.pointSize
	property real mediumFont: window.font.pointSize + 2
	property real largeFont: window.font.pointSize + 4

    Material.accent: "#41cd71"
    Material.primary: "#41cd71"

	property var buttonColor: Material.accent

	SwipeView {
		id: swipeview
		interactive: false
		anchors.fill: parent

		StartPage {
			id: sp
		}

		PreparePage {
			id: prp
		}

		ProcessPage {
			id: pp
		}

		ResultPage {
			id: rp
        }

        About {
            id: ab
        }

	}

}
