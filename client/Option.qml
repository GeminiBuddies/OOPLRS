import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

Rectangle {
    id: rectangle
    width: 640
    height: 480
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#91e0c8"
        }
    }
    border.color: "#00000000"

    Text {
        id: text0
        x: 208
        y: 42
        width: 224
        height: 55
        color: "#cb9f06"
        text: qsTr("设置")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 45
    }

    GridLayout {
        objectName: "gridLayout"
        x: 107
        y: 134
        columnSpacing: 15
        rowSpacing: 15
        rows: 4
        columns: 3

        Text {
            id: text4
            color: "#1572cf"
            text: qsTr("游戏昵称")
            Layout.preferredHeight: 43
            Layout.preferredWidth: 150
            elide: Text.ElideNone
            font.pixelSize: 35
        }

        Item {
            id: spacer
            Layout.preferredWidth: 14
            Layout.preferredHeight: 14
        }

        TextInput {
            id: textInput
            objectName: "nameInput"
            Layout.preferredHeight: 43
            Layout.preferredWidth: 200
            font.pixelSize: 35
        }

        Text {
            id: text1
            color: "#1572cf"
            text: qsTr("游戏音效")
            Layout.preferredHeight: 54
            Layout.preferredWidth: 150
            font.family: "Arial"
            font.pixelSize: 35
        }

        CheckBox {
            id: checkBox1
            objectName: "checkBox1"
        }

        Slider {
            id: slider1
            objectName: "slider1"
            value: 0.5
        }

        Text {
            id: text2
            color: "#1572cf"
            text: qsTr("语音音效")
            Layout.preferredHeight: 46
            Layout.preferredWidth: 150
            font.pixelSize: 35
        }

        CheckBox {
            id: checkBox2
            objectName: "checkBox2"
        }

        Slider {
            id: slider2
            objectName: "slider2"
            value: 0.5
        }

        Text {
            id: text3
            color: "#1572cf"
            text: qsTr("提示音")
            Layout.preferredHeight: 44
            Layout.preferredWidth: 150
            font.pixelSize: 35
        }

        CheckBox {
            id: checkBox3
            objectName: "checkBox3"
        }

        Slider {
            id: slider3
            objectName: "slider3"
            value: 0.5
        }
    }

    RowLayout {
        x: 263
        y: 390
        spacing: 80
        objectName: "rowLayout"

        Text {
            id: text5
            objectName: "confirm"
            color: "#821c87"
            text: qsTr("确定")
            Layout.preferredHeight: 49
            Layout.preferredWidth: 115
            verticalAlignment: Text.AlignVCenter
            styleColor: "#00000000"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30

            MouseArea {
                id: mouseArea
                objectName: "mouseArea"
                anchors.fill: parent
            }
        }
    }

}
