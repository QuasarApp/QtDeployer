import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Page {
	id: page
	clip: true
	width: listview.width

	property var model
	property bool checkable
	property bool expanded

	height: expanded ? implicitHeight:header.height

	background: Rectangle {
		color: "#eee"
	}

	Behavior on height {
		SmoothedAnimation {
			velocity: page.implicitHeight*2
		}
	}

	header: AbstractButton {
		id: head
		padding: 6
		onClicked: expanded = !expanded

		background: Rectangle {
			color: Material.background

			Rectangle {
				height: 1
				width: parent.width
				color: Material.accent
				anchors.bottom: parent.bottom
			}
		}

		contentItem: RowLayout {
			Label {
				text: "▶"
				rotation: expanded ? 90:0
				font.pointSize: mediumFont

				Behavior on rotation {
					NumberAnimation {}
				}
			}

			Label {
				leftPadding: 6
				text: page.title
				Layout.fillWidth: true
				elide: Text.ElideRight
				font.pointSize: mediumFont
			}
		}
	}

	contentItem: Column {
		Repeater {
			model: page.model

			delegate: Label {
				id: label
				padding: 10
				width: parent.width
				elide: Text.ElideRight

				text: (page.checkable ? (OutputManager.copySuccess[index]
										 ? "✔   ":"🞪   "):"") + modelData
			}
		}
	}

	Rectangle {
		height: 1
		parent: page
		width: parent.width
		color: Material.primary
		anchors.bottom: parent.bottom
	}
}
