import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Werewolf")
    objectName: "mainWindow"

    MainForm {
        id: mainForm
        x: -320
        y: -200
        width: 1280
        height: 800
        border.color: "#00000000"
        anchors.fill: parent
        objectName: "mainForm"
    }

    ServerList{
        id: serverList
        visible: false
        x: 0
        y: 0
        width: 640
        height: 480
        objectName: "serverList"
    }



    Option{
        objectName: "option"
        visible: false
        z: 2147483647

    }

    WelcomeForm{
        id: welcomeForm
        objectName: "welcomeForm"
        visible: true
        width: 640
        height: 480

    }

    Connections{
        target: welcomeForm
        onSetPlayer:{
            serverList.visible=true
            welcomeForm.visible=false
            serverList.setFocus()
        }
    }


}
