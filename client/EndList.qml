import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id:endList
    width:640
    height: 480
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#62e3eb"
        }
    }
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
                    text: "玩家编号"
                    width:300
                    font.bold: true
                    font.pixelSize: 40
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Text{
                    text: "玩家身份"
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
                    text: playerNumber
                    width: 300
                    font.pixelSize: 40
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Text{
                    text: playerCharacter
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
        objectName: "exit"
        x: 270
        y: 406
        text: qsTr("退出")
        visible:false
        signal exit()
        onClicked:{
            exit();
        }
    }

    function addElement(playerNumber, playerCharacter){
        myModel.append({
                           "playerNumber": playerNumber,
                           "playerCharacter": playerCharacter
                       }
                       )
    }

}
