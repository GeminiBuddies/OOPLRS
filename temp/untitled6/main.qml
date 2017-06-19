import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextEdit {
        id: textEdit
        x: 59
        y: 219
        width: 523
        height: 42
        text: qsTr("Text Edit")
        font.pixelSize: 30
    }
}
