import QtQuick 2.0

Item {
    width: 380
    height: 200

    Rectangle {
        id: rectangle1
        color: "#f9ee38"
        anchors.fill: parent

        Text {
            id: text1
            x: 49
            y: 79
            width: 292
            height: 64
            text: qsTr("Function Space")
            font.pixelSize: 40
        }
    }

}
