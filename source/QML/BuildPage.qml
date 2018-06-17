import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Page {
    id: page
    clip: false

    header: Header {
        message: qsTr("Qt Deployer")
    }

    property string outdir
    property var cpplibs: []

    Flickable {
         id: flick

         Connections {
             target: BuildManager
             onLogChanged:{
                 log.append(BuildManager.log)
             }
         }

         Connections {
             target: BuildManager
             onFinished:{
                 swipeview.currentIndex = 2
                 CppManager.cppLibraries = cpplibs
             }
         }

         anchors.fill: parent
         contentWidth: log.paintedWidth
         contentHeight: log.paintedHeight
         clip: true

         function ensureVisible(r)
         {
             if (contentX >= r.x)
                 contentX = r.x;
             else if (contentX+width <= r.x+r.width)
                 contentX = r.x+r.width-width;
             if (contentY >= r.y)
                 contentY = r.y;
             else if (contentY+height <= r.y+r.height)
                 contentY = r.y+r.height-height;
         }

         TextEdit {
             id: log
             width: flick.width
             focus: true
             wrapMode: TextEdit.Wrap
             onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
         }
     }

}
