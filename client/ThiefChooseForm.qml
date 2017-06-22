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
            color: "#05f188"
        }
    }


    signal thiefChoose(int i)

    RowLayout {
        x: 75
        y: 83
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20
        objectName: "rowLayout"

        Image {
            id: image
            Layout.preferredHeight: 150
            Layout.preferredWidth: 150
            source: "qrc:/images/images/townsfolk.jpg"
        }

        Image {
            id: image1
            objectName: "image1"
            Layout.preferredHeight: 150
            Layout.preferredWidth: 150
            source: ""
        }

        Image {
            id: image2
            objectName: "image2"
            Layout.preferredHeight: 150
            Layout.preferredWidth: 150
            source: ""
        }
    }

    RowLayout {
        x: 141
        y: 272
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 125

        RadioButton {
            id: radioButton
            checked: true
        }

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
            if(radioButton.checked==true)
                thiefChoose(0)
            else if(radioButton1.checked==true)
                thiefChoose(1)
            else if(radioButton2.checked==true)
                thiefChoose(2)
        }
    }

}
