import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
	id: window
	visible: true
	title: qsTr("Qt Linux Deployer")

	width: 600
	height: sp.implicitHeight + 30

	property real smallFont: window.font.pointSize
	property real mediumFont: window.font.pointSize + 2
	property real largeFont: window.font.pointSize + 4

	Material.accent: Material.Red
	Material.primary: Material.Red

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
	}
}
