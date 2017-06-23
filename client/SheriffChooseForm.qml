import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

Rectangle{
    id: rectangle
    opacity: 0.7
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#1ae7f3"
        }
    }


    signal sheriffChoose(int i)

    RowLayout {
        x: 75
        y: 83
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20
        objectName: "rowLayout"

        Image {
            id: image1
            objectName: "image1"
            Layout.preferredHeight: 150
            Layout.preferredWidth: 150
            source: "qrc:/images/images/sheriff.jpg"
        }
    }

    RowLayout {
        x: 141
        y: 272
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 125

        RadioButton {
            id: radioButton1
        }

        RadioButton {
            id: radioButton2
        }
    }
    Button {
        id: button
        x: 270
        y: 383
        text: qsTr("确定")

        onClicked:{
            rectangle.visible=false
            if(radioButton1.checked==true)
                sheriffChoose(1)
            else if(radioButton2.checked==true)
                sheriffChoose(2)
        }
    }

    Text {
        id: text1
        x: 202
        y: 327
        width: 64
        height: 33
        text: qsTr("竞选")
        font.pixelSize: 30
    }

    Text {
        id: text2
        x: 358
        y: 327
        width: 96
        height: 33
        text: qsTr("不竞选")
        font.pixelSize: 30
    }

}
