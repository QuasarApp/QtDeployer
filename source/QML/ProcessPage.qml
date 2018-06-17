import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Page {
	id: page
	clip: true

	property bool erase
	property int state: MainManager.state

    header: Header {
        message: qsTr("Qt Deployer")
    }

	Button {
		width: 200
		padding: 18
		anchors.centerIn: parent
		Material.background: buttonColor
        text: page.state == 0 ? "Go!":(page.state == 1 ? qsTr("Wait!"):qsTr("Done!"))

		onClicked: {
			if (page.state == 0)
				MainManager.start(erase)
			else if (page.state == 2)
                swipeview.currentIndex = 4
		}
	}
}
