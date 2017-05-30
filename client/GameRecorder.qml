import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: item1
    width: 400
    height: 250

    Text {
        id: text1
        anchors.fill: parent
        font.pixelSize: 12
    }
    function showMessage(str){
        textArea1.append(str)
    }

    Flickable {
        id: flickable1
        width: 390
        height: 250
        enabled: true
        interactive: true
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        TextArea.flickable: TextArea {
            id: textArea1
            width: 390
            height: 250
            readOnly: true
            wrapMode: TextArea.Wrap
            font.pixelSize: 20
            color: "black"
        }
        ScrollBar.vertical: ScrollBar {
            id: scrollBar1
            anchors.bottom: parent.bottom
            anchors.top:parent.top
        }
    }

    Rectangle {
        id: rectangle1
        opacity:0.5
        width: 400
        height: 250
        color: "#1b74ff"
        z: -1
        anchors.top: parent.top
        anchors.left: parent.left
    }

}
