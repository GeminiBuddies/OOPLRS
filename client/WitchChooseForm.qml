import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

Rectangle{
    id: rectangle
    opacity:0.7
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#05f188"
        }
    }


    signal witchChoose(int i)
        RadioButton {
            id: radioButton
            x: 129
            y: 267
            checked: true
        }

        RadioButton {
            id: radioButton1
            x: 297
            y: 267
            objectName: "button1"
        }

        RadioButton {
            id: radioButton2
            x: 468
            y: 267
            objectName:"button2"
        }
    Button {
        id: button
        x: 270
        y: 383
        text: qsTr("确定")

        onClicked:{
            rectangle.visible=false
            if(radioButton.checked==true)
                witchChoose(0)
            else if(radioButton1.checked==true)
                witchChoose(1)
            else if(radioButton2.checked==true)
                witchChoose(2)
        }
    }

    Text {
        id: text1
        x: 77
        y: 153
        color: "#9898b9"
        text: qsTr("不使用")
        font.bold: true
        font.pixelSize: 50
    }

    Text {
        id: text2
        x: 270
        y: 153
        color: "#e55151"
        text: qsTr("毒药")
        font.bold: true
        font.pixelSize: 50
    }

    Text {
        id: text3
        x: 441
        y: 153
        color: "#1919c7"
        text: qsTr("解药")
        font.bold: true
        font.pixelSize: 50
    }

}
