import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: item1
    width: 400
    height: 250

    Flickable {
        id: flickable1
        objectName: "flickable1"
        width: 300
        height: 170
        clip: false
        boundsBehavior: Flickable.StopAtBounds
        interactive: true
        flickableDirection: Flickable.VerticalFlick
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        TextArea.flickable: TextArea {
            id: textArea1
            width: 387
            height: 217
            objectName: "textArea1"
            readOnly: true
            wrapMode: TextArea.Wrap
            font.pixelSize: 20
            color: "black"
        }
        ScrollBar.vertical: ScrollBar {
        }
    }

    function showMessage(str){
        textArea1.append(str);
    }
    Rectangle {
        id: rectangle1
        y: 160
        width: 400
        height: 30
        color: "#00000000"
        border.width: 2
        border.color: "#d6b97b"
        z: -1
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    Rectangle {
        id: rectangle2
        height: 170
        opacity: 0.5
        color: "#1b74ff"
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        border.width: 2
        border.color: "#d6b97b"
        anchors.bottomMargin: 30
        z: -2
        anchors.fill: parent
    }

    signal sendMessage(string str)
    TextInput {
        id: textInput1
        objectName: "sendBox"
        y: 172
        width: 390
        height: 25
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 5
        font.pixelSize: 20 
        property bool canChat
        Component.onCompleted: {
            canChat=true
        }
        onAccepted:{
            if(canChat==true){
                sendMessage(text)
                text=""
            }
        }
    }




}
