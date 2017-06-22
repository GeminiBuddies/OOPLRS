import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id:serverList
    width:640
    height: 480
    color: "#EEEEEE"
    function setFocus(){
        listView1.focus=true
    }

    ListView {
        id: listView1
        x: 0
        y: 5
        width: 640
        height: 480
        boundsBehavior: Flickable.DragAndOvershootBounds
        header: Item{
            id: myHeader
            x: 5
            width: 640
            height: 60
            Row{
                x:0
                y:0
                Text{
                    text: "服务器编号"
                    width:300
                    font.bold: true
                    font.pixelSize: 40
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Text{
                    text: "名称"
                    width: 300
                    font.bold: true
                    font.pixelSize: 40
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                spacing: 40

            }

        }

        delegate: Item {
            id: myDelegate
            x: 5
            width: 640
            height: 60
            MouseArea{
                id: mouseArea
                anchors.fill: parent
                onClicked:{
                    listView1.currentIndex=index
                    listView1.focus=true
                }
            }
            Row {
                id: row1
                x: 0
                y: 0
                Text{
                    text: number
                    width: 300
                    font.pixelSize: 40
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Text{
                    text: serverName
                    width: 300
                    font.pixelSize: 40
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                spacing: 40
            }
        }
        model: ListModel {
            id: myModel

        }
        focus: true
        highlight: Rectangle{
            color: "lightblue"
        }
    }

    Button {
        id: button
        objectName: "confirm"
        x: 130
        y: 407
        text: qsTr("确定")
        visible:false
        signal connectServer(int index)
        onClicked:{
            listView1.focus=true
            connectServer(listView1.currentIndex);
        }
    }

    Button {
        id: button1
        objectName: "refresh"
        x: 395
        y: 407
        text: qsTr("刷新")
        signal getServer()
        onClicked:{
            listView1.focus=true
            getServer()
        }
    }
    function clear(){
        myModel.clear();
    }

    function addElement(number, serverName){
        myModel.append({
                           "number": number,
                           "serverName": serverName
                       }
                       )
    }

}
