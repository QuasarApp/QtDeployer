import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Page {
	id: page
	clip: true

    header: Header {
        message: qsTr("Qt Deployer")
    }

	property string outdir
	property var cpplibs: []

	ColumnLayout {
		spacing: 15
		anchors.margins: 15
		anchors.fill: parent

		Label {
			elide: Text.ElideRight
			Layout.fillWidth: true
			font.pointSize: mediumFont
            text: qsTr("Choose Non-Qt Libraries To Copy")
		}

		Flickable {
			id: flick
			Layout.fillWidth: true
			Layout.fillHeight: true
			contentWidth: width
			contentHeight: column.height
			clip: true

			ScrollBar.vertical: ScrollBar { }

			Rectangle {
				parent: flick
				anchors.fill: parent
				color: "transparent"
				border.color: Material.accent
			}

			Column {
				id: column
				width: parent.width

				Repeater {
                    model: CppManager.cppLibraries

					delegate: CheckDelegate {
						id: del
						text: modelData
						width: parent.width

						Connections {
							target: checkAll
							onCheckedChanged: del.checked = checkAll.checked
						}

						onCheckedChanged: {
							var place = cpplibs.indexOf(del.text)

							if (checked && place < 0)
								cpplibs.push(del.text)
							else if (place > -1)
								cpplibs.splice(place, 1)
						}
					}
				}
			}
		}

		CheckBox {
			id: checkAll
			Layout.fillWidth: true
            text: qsTr("Check All The Above")
		}

		CheckBox {
			id: erase
			Layout.fillWidth: true
            text: qsTr("Erase Everything In: ") + outdir
		}

		Button {
            text: qsTr("Next")
			Material.background: buttonColor
			Layout.alignment: Qt.AlignRight

			onClicked: {
				pp.erase = erase.checked
                swipeview.currentIndex = 3
				CppManager.cppLibraries = cpplibs
			}
		}
	}

	Settings {
		property alias erase: erase.checked
	}
}
