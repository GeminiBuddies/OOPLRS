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
            x: 57
            y: 97
            width: 21
            height: 23
            color: "#0c16c6"
            text:""
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.bold: true
            font.pixelSize: 20
            horizontalAlignment: Text.AlignRight
            objectName: "number"
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
        anchors.topMargin: 93
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
        anchors.topMargin: 40
        source: ""
        objectName: "characterImage"
    }

    Text {
        id: text1
        y: 160
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
        visible: false
        anchors.top: parent.top
        anchors.topMargin: 10
        source: "qrc:/images/images/vote.png"
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

    Image {
        id: image3
        x: 25
        y: 17
        width: 30
        height: 29
        visible: false
        source: "qrc:/images/images/sheriff.jpg"
        objectName:"sheriffImage"
    }

    Image {
        id: image4
        x: 25
        y: 17
        width: 30
        height: 29
        opacity: 0.5
        objectName: "piedPiperImage"
        visible: false
        source: "qrc:/images/images/puzzled.jpg"
    }

    Image {
        id: image5
        x: 21
        y: 17
        width: 40
        height: 40
        z: 1
        opacity: 0.5
        visible: false
        objectName: "arrowImage"
        source: "qrc:/images/images/arrow.png"
    }
}
