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


	ColumnLayout {
		spacing: 15
		anchors.margins: 15
		anchors.fill: parent

		PathChooser {
			id: qtdir
            title: qsTr("Qt Build Directory")
            content: MainManager.qtDir();
		}

		PathChooser {
            id: projectfile
            title: qsTr("Project File")
            isdir: false

		}

        PathChooser {
            id: icon
            title: qsTr("Project icon")
            isdir: false
        }

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}

		Button {
            text: qsTr("Next")
			Material.background: buttonColor
			Layout.alignment: Qt.AlignRight
            enabled: qtdir.confirmed && projectfile.confirmed

			onClicked: {
                MainManager.prepare(qtdir.content, projectfile.content, icon.content)

                prp.outdir = MainManager.outDir
				swipeview.currentIndex = 1
			}
		}
	}
}
