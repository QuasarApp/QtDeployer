import QtQuick 2.7
import QtQuick.Controls 2.0

ToolBar {
	id: control

	property string text

	Label {
		text: control.text
		anchors.centerIn: parent
		font.pointSize: control.font.pointSize + 3
	}
}
