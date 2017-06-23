import QtQuick 2.6
import QtQuick.Controls 2.0

Rectangle {
    id: rectangle
    visible: false
    width: 1280
    height: 800
    color: "#00000000"
    property alias mouseArea: mouseArea
    property alias myTimer: myTimer
    property alias thiefChooseForm: thiefChooseForm
    z: 2147483646

    CharacterImage {
        id: characterImage1
        x: 102
        y: 100
        width: 80
        height: 180
        anchors.left: parent.left
        anchors.leftMargin: 241
        anchors.top: parent.top
        anchors.topMargin: 154
        objectName: "characterImage1"
    }

    CharacterImage {
        id: characterImage2
        x: 192
        y: 90
        width: 80
        height: 180
        anchors.bottom: characterImage1.bottom
        anchors.bottomMargin: 10
        anchors.left: characterImage1.right
        anchors.leftMargin: 10
        objectName: "characterImage2"
    }

    CharacterImage {
        id: characterImage3
        x: 282
        y: 70
        width: 80
        height: 180
        anchors.bottom: characterImage2.bottom
        anchors.bottomMargin: 20
        anchors.left: characterImage2.right
        anchors.leftMargin: 10
        objectName:"characterImage3"
    }

    CharacterImage {
        id: characterImage4
        x: 372
        y: 60
        width: 80
        height: 180
        anchors.bottom: characterImage3.bottom
        anchors.bottomMargin: 10
        anchors.left: characterImage3.right
        anchors.leftMargin: 10
        objectName: "characterImage4"
    }

    CharacterImage {
        id: characterImage5
        x: 462
        y: 55
        width: 80
        height: 180
        anchors.left: characterImage4.right
        anchors.leftMargin: 10
        anchors.top: characterImage4.top
        anchors.topMargin: -5
        objectName: "characterImage5"
    }

    CharacterImage {
        id: characterImage6
        x: 552
        y: 65
        width: 80
        height: 180
        anchors.left: characterImage5.right
        anchors.leftMargin: 10
        anchors.top: characterImage5.top
        anchors.topMargin: 10
        objectName: "characterImage6"
    }

    CharacterImage {
        id: characterImage7
        x: 642
        y: 85
        width: 80
        height: 180
        anchors.left: characterImage6.right
        anchors.leftMargin: 10
        anchors.top: characterImage6.top
        anchors.topMargin: 20
        objectName: "characterImage7"
    }

    CharacterImage {
        id: characterImage8
        x: 732
        y: 95
        width: 80
        height: 180
        anchors.top: characterImage7.top
        anchors.topMargin: 10
        anchors.left: characterImage7.right
        anchors.leftMargin: 10
        objectName: "characterImage8"
    }

    CharacterImage {
        id: characterImage9
        x: 822
        y: 105
        width: 80
        height: 180
        anchors.top: characterImage8.top
        anchors.topMargin: 10
        anchors.left: characterImage8.right
        anchors.leftMargin: 10
        objectName: "characterImage9"
    }

    CharacterImage {
        id: characterImage10
        x: 907
        y: 205
        width: 80
        height: 180
        anchors.left: characterImage9.right
        anchors.leftMargin: 5
        anchors.top: characterImage9.top
        anchors.topMargin: 100
        objectName: "characterImage10"
    }

    CharacterImage {
        id: characterImage11
        x: 817
        y: 275
        width: 80
        height: 180
        anchors.top: characterImage10.bottom
        anchors.topMargin: -50
        anchors.right: characterImage10.left
        anchors.rightMargin: 10
        objectName: "characterImage11"
    }

    CharacterImage {
        id: characterImage12
        x: 727
        y: 275
        width: 80
        height: 180
        anchors.top: characterImage11.top
        anchors.topMargin: 0
        anchors.right: characterImage11.left
        anchors.rightMargin: 10
        objectName: "characterImage12"
    }

    CharacterImage {
        id: characterImage13
        x: 637
        y: 275
        width: 80
        height: 180
        anchors.right: characterImage12.left
        anchors.rightMargin: 10
        anchors.top: characterImage12.top
        anchors.topMargin: 0
        objectName: "characterImage13"
    }

    CharacterImage {
        id: characterImage14
        x: 547
        y: 265
        height: 180
        anchors.top: characterImage13.top
        anchors.topMargin: -10
        anchors.right: characterImage13.left
        anchors.rightMargin: 10
        objectName: "characterImage14"
    }

    CharacterImage {
        id: characterImage15
        x: 457
        y: 265
        height: 180
        anchors.top: characterImage14.top
        anchors.topMargin: 0
        anchors.right: characterImage14.left
        anchors.rightMargin: 10
        objectName: "characterImage15"
    }

    CharacterImage {
        id: characterImage16
        x: 367
        y: 265
        height: 180
        anchors.top: characterImage15.top
        anchors.topMargin: 0
        anchors.right: characterImage15.left
        anchors.rightMargin: 10
        objectName: "characterImage16"
    }

    CharacterImage {
        id: characterImage17
        x: 277
        y: 275
        height: 180
        anchors.right: characterImage16.left
        anchors.rightMargin: 10
        anchors.top: characterImage16.top
        anchors.topMargin: 10
        objectName: "characterImage17"
    }

    CharacterImage {
        id: characterImage18
        x: 187
        y: 275
        height: 180
        anchors.top: characterImage17.top
        anchors.topMargin: 0
        anchors.right: characterImage17.left
        anchors.rightMargin: 10
        objectName: "characterImage18"
    }

    CharacterImage {
        id: characterImage19
        x: 97
        y: 275
        height: 180
        anchors.top: characterImage18.top
        anchors.topMargin: 0
        anchors.right: characterImage18.left
        anchors.rightMargin: 10
        objectName: "characterImage19"
    }

    CharacterImage {
        id: characterImage20
        x: 12
        y: 205
        width: 80
        height: 180
        anchors.top: characterImage10.top
        anchors.topMargin: 0
        anchors.right: characterImage19.left
        anchors.rightMargin: 5
        objectName: "characterImage20"
    }

    Image {
        id: image1
        z: -1
        anchors.fill: parent
        source: "qrc:/images/images/village.jpg"
    }

    /*FunctionSpace {
        id: functionSpace1
        x: 310
        y: 400
        z: 9
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: universeDialog1.right
        anchors.leftMargin: 0
    }*/

    /*Button {
        id: button2
        x: 910
        y: 30
        width: 60
        height: 50
        text: qsTr("exit")
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 30
    }

    Button {
        id: button1
        x: 840
        y: 30
        width: 60
        height: 50
        text: qsTr("start")
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.right: button2.left
        anchors.rightMargin: 10
    }*/

    GameRecorder {
        id: gameRecorder1
        x: 690
        y: 400
        width: 400
        height: 250
        z: 7
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        objectName: "gameRecorder1"
    }

    ChatBox {
        id: chatBox1
        x: 0
        y: 400
        width: 400
        height: 250
        z: 8
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        objectName: "universeDialog1"
    }

    Rectangle {
        id: weather
        color: "#000000"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: true
        z: 6
        objectName: "weather"

        PropertyAnimation{
            objectName: "night"
            target: weather
            property: "opacity"
            to: 0.8
            duration: 1000
            running: false
        }

        PropertyAnimation{
            objectName: "day"
            target: weather
            property: "opacity"
            to: 0
            duration: 1000
            running: true
        }

        PropertyAnimation{
            objectName: "roleActionStart"
            target: weather
            property: "opacity"
            to: 0.6
            duration: 500
            running: false
        }

        PropertyAnimation{
            objectName: "roleActionEnd"
            target: weather
            property: "opacity"
            to: 0.8
            duration: 1000
            running: false
        }
    }

    MyTimer{
        id: myTimer
        objectName: "timer"
        width: 100
        height: 100
        anchors.left: parent.left
        anchors.leftMargin: 110
        anchors.top: parent.top
        anchors.topMargin: 67

    }

    ThiefChooseForm{
        id: thiefChooseForm
        objectName: "thiefChooseForm"
        x: 316
        y: 176
        width: 640
        height: 480
        z: 9
        visible: false

    }

    WitchChooseForm{
        id: witchChooseForm
        x: 316
        y: 176
        width: 640
        height: 480
        visible: false
        z: 10
        objectName: "witchChooseForm"
    }

    SheriffChooseForm{
        id:sheriffChooseForm
        x: 316
        y: 176
        objectName: "sheriffChooseForm"
        width: 640
        height: 480
        z: 11
        visible:false
    }

    SheriffChooseVoteOrderForm{
        id:sheriffChooseVoteOrderForm
        x: 316
        y: 176
        objectName: "sheriffChooseVoteOrderForm"
        width: 640
        height: 480
        z: 13
        visible:false
    }

    EndList{
        id: endList
        visible: false
        x: 316
        y: 176
        width: 640
        height: 480
        z: 12
        objectName: "endList"
    }

    Text {
        id: text1
        x: 251
        y: 124
        objectName: "bigText"
        color: "#1e54e1"
        text: qsTr("角色行动开始")
        font.bold: true
        anchors.verticalCenter: parent.verticalCenter
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 150
    }

    signal sheriffExit()
    Rectangle {
        id: rectangle1
        x: 581
        y: 633
        width: 100
        height: 50
        color: "#25f20d"
        visible: false
        objectName: "sheriffExit"
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            z: -1
            objectName: "sheriffExitButton"
            onClicked: {
                sheriffExit()
                rectangle1.visible=false
            }
        }

        Text {
            id: text2
            text: "退水"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            z: 1
            anchors.fill: parent
            font.pixelSize: 30
        }
    }
}
