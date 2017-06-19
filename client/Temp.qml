import QtQuick 2.0

Rectangle{
    signal sendMessage(string str)
    width: 459
    height: 73
    TextInput {
        id: textInput1
        objectName: "sendBox"
        y: 0
        width: 459
        height: 73
        color: "#000000"
        z: 3
        font.family: "Arial"
        selectionColor: "#433fee"
        font.pixelSize: 30
        x: 0
        onAccepted:{
            sendMessage(text)
            text=""
        }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 459
        height: 73
        color: "#fa2a2a"
        border.width: 2
        border.color: "#1454d4"
        z: 2
    }

}
