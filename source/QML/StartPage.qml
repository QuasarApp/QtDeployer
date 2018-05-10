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
		}

		PathChooser {
			id: execpath
			isdir: false
            title: qsTr("Executable File Path")
		}

		PathChooser {
			id: projectdir
            title: qsTr("Project Directory")
		}

		PathChooser {
			id: outdir
            title: qsTr("Final Output Directory")
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}

		Button {
            text: qsTr("Next")
			Material.background: buttonColor
			Layout.alignment: Qt.AlignRight
			enabled: qtdir.confirmed && execpath.confirmed
					 && projectdir.confirmed && outdir.confirmed

			onClicked: {
				MainManager.prepare(qtdir.content, execpath.content,
									projectdir.content, outdir.content)

				prp.outdir = outdir.content
				swipeview.currentIndex = 1
			}
		}
	}
}
