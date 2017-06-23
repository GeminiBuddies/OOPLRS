import QtQuick 2.0

Rectangle {
    id: background
    width: 80
    height: 180
    color: "#00000000"
    visible: true


    MouseArea {
        id: mouseArea1
        enabled: false
        objectName: "mouseArea1"
        signal mouseAreaClicked();
        signal rightClicked();
        width: 80
        height: 120
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 0
        onClicked:{
            mouseAreaClicked();
        }

        Text {
            id: text3
            x: 55
            y: 99
            width: 21
            height: 23
            color: "#0c16c6"
            text:""
            font.bold: true
            font.pixelSize: 20
            horizontalAlignment: Text.AlignRight
        }
    }

    Image {
        id: image1
        opacity:0.5
        width: 40
        height: 40
        source: ""
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 73
        objectName: "role"
    }

    Image {
        id: image
        width: 80
        height: 120
        fillMode: Image.PreserveAspectFit
        z: -1
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 20
        source: ""
        objectName: "characterImage"
    }

    Text {
        id: text1
        y: 128
        width: 80
        height: 20
        horizontalAlignment: Text.AlignHCenter
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        font.pixelSize: 14
        objectName: "characterName"
    }

    Image {
        id: image2
        x: 35
        width: 68
        height: 100
        anchors.top: parent.top
        anchors.topMargin: 10
        source: "qrc:/images/images/vote.png"
        visible: false
        objectName: "voteImage"

        Text {
            id: text2
            width: 40
            height: 23
            text: qsTr("")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.leftMargin: 13
            anchors.top: parent.top
            anchors.topMargin: 13
            font.pixelSize: 17
            objectName: "voteText"
        }
    }
}
