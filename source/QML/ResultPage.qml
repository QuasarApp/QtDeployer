import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Page {
	clip: true

	header: TopBar {
		text: "Result"

		ToolButton {
			text: "➔"
			rotation: 180
			font.pointSize: largeFont
			anchors.right: parent.right
			onClicked: swipeview.currentIndex = 0
			anchors.verticalCenter: parent.verticalCenter
		}
	}

	ListView {
		id: listview
        anchors.fill: parent
		ScrollBar.vertical: ScrollBar {}

		model: VisualItemModel {
			ExtendableView {
				checkable: false
				title: "Qt Libraries"
				model: CppManager.qtLibraries
			}

			ExtendableView {
				checkable: false
				title: "Non-Qt Libraries"
				model: CppManager.cppLibraries
			}

			ExtendableView {
				checkable: false
				title: "Unknown Libraries"
				model: CppManager.notFoundLibs
			}

			ExtendableView {
				checkable: false
				title: "Qml Imports"
				model: QmlManager.foundImports
			}

			ExtendableView {
				checkable: false
				title: "Failed Qml Imports"
				model: QmlManager.notFoundImports
			}

			ExtendableView {
				checkable: true
				title: "Copied Paths"
				model: OutputManager.pathsToCopy
			}
		}
    }
}
