import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle {
    color: "#00000000"
    QtObject{
        id: attrs;
        objectName: "attrs"
        property int counter
        Component.onCompleted: {
            attrs.counter=30;
        }
    }

    Text{
        id: countShow;
        objectName: "text"
        anchors.centerIn:parent;
        color: "Blue"
        font.pixelSize:80
    }

    Timer{
        objectName: "timer"
        id:timer
        interval: 1000
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            countShow.visible=true
            countShow.text=attrs.counter;
            attrs.counter-=1
            if(attrs.counter>=20)
                countShow.color="Green"
            else if(attrs.counter>=10)
                countShow.color="Yellow"
            else if(attrs.counter>=0)
                countShow.color="red"
            if(attrs.counter<0) {
                timer.stop()
                countShow.visible=false
            }
        }
    }

}
