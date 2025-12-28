import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 1000
    height: 700
    visible: true
    title: "Smart Home"

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            spacing: 12
            Label {
                text: "Smart Home"
                font.pixelSize: 20
                Layout.leftMargin: 12
                Layout.alignment: Qt.AlignVCenter
            }
            Item { Layout.fillWidth: true }
            ComboBox {
                id: roomBox
                Layout.rightMargin: 12
                model: ["All", "Living Room", "Hall", "Kitchen", "Bedroom", "Garage"]
                onCurrentTextChanged: {
                    devicesModel.roomFilter = currentText === "All" ? "" : currentText
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        // Summary
        RowLayout {
            spacing: 24
            Label { text: `Devices: ${grid.count}` }
            Label {
                text: {
                    var online = 0
                    for (var i = 0; i < grid.count; ++i) {
                        var d = devicesModel.get(i)
                        if (d && d.online) online++
                    }
                    return `Online: ${online}`
                }
            }
        }

        // Devices grid
        GridView {
            id: grid
            Layout.fillWidth: true
            Layout.fillHeight: true
            cellWidth: 280
            cellHeight: 160
            model: devicesModel
            delegate: DeviceTile {
                width: grid.cellWidth - 16
                height: grid.cellHeight - 16
                deviceId: id
                name: model.name
                room: model.room
                type: model.type
                online: model.online
                power: model.power
                brightness: model.brightness
                temperature: model.temperature
            }
            ScrollBar.vertical: ScrollBar {}
        }
    }
}

