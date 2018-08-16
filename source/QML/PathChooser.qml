import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ColumnLayout {
	id: root
	Layout.fillHeight: false

	property string title
	property bool isdir: true
	property bool confirmed: false
	property alias content: field.text

	Label {
		text: title
		elide: Text.ElideRight
		Layout.fillWidth: true
		font.pointSize: mediumFont
	}

	RowLayout {
		Layout.fillHeight: false

		TextField {
			id: field
			Layout.fillWidth: true
            placeholderText: qsTr("Enter path or browse")

			onTextChanged: {
				if (!MainManager.pathExists(isdir, text))
				{
                    wlabel.text = qsTr("Path doesn't exist")
					confirmed = false
				}
				else if (!MainManager.hasPrems(text))
				{
                    wlabel.text = qsTr("I don't have permission to access this path")
					confirmed = false
				}
				else
				{
                    wlabel.text = qsTr("This path is OK")
					confirmed = true
				}
			}
		}

		Button {
            text: qsTr("Browse")
			onClicked: fd.open()
			Material.background: buttonColor
		}
	}

	Label {
		id: wlabel
		elide: Text.ElideRight
		Layout.fillWidth: true
	}

	FileDialog {
		id: fd
		selectFolder: isdir
		selectMultiple: false

		onAccepted: field.text = MainManager.stringFromUrl(isdir ? folder:fileUrl)
	}
}
