import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle{
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#2a99d0"
        }
    }

    Text {
        id: text1
        x: 120
        y: 72
        color: "#560fe3"
        text: qsTr("请选择您的性别和昵称")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 40
    }

    Image {
        id: image
        x: 81
        y: 171
        width: 140
        height: 226
        source: "qrc:/images/images/man1.png"

        Rectangle {
            id: rectangle1
            color: "#00000000"
            border.color: "#8a10d8"
            anchors.fill: parent
        }
    }

    Text {
        id: text2
        x: 302
        y: 269
        text: qsTr("昵称：")
        font.pixelSize: 30
    }

    TextInput {
        id: textInput
        x: 419
        y: 269
        width: 148
        height: 30
        font.pixelSize: 30

        Rectangle {
            id: rectangle
            x: -5
            y: 0
            width: 153
            height: 30
            color: "#00000000"
            border.color: "#801de2"
            z: -2
        }
    }
    signal setPlayer(string name, bool isBoy)
    Button {
        id: button
        x: 371
        y: 344
        text: qsTr("确定")
        onClicked:{
            setPlayer(textInput.text, radioButton.checked)
        }
    }

    RadioButton {
        id: radioButton
        x: 317
        y: 193
        checked: true
        text: qsTr("男")
        onClicked:{
            image.source="qrc:/images/images/man1.png"
        }
    }

    RadioButton {
        id: radioButton1
        x: 463
        y: 193
        text: qsTr("女")
        onClicked: {
            image.source="qrc:/images/images/woman.png"
        }
    }

}
