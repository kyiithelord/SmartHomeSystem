import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: tile
    radius: 12
    color: online ? (power ? "#e8fff0" : "#f6f6f6") : "#fff0f0"
    border.width: 1
    border.color: "#dddddd"
    property int deviceId: -1
    property string name: ""
    property string room: ""
    property string type: ""
    property bool online: true
    property bool power: false
    property int brightness: 0
    property real temperature: 0

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        RowLayout {
            spacing: 8
            Label { text: name; font.bold: true; Layout.fillWidth: true }
            Label { text: room; color: "#666" }
        }

        RowLayout {
            spacing: 12
            Label { text: `Type: ${type}`; color: "#444" }
            Label { text: online ? "Online" : "Offline"; color: online ? "#2e7d32" : "#b71c1c" }
            Switch {
                id: powerSwitch
                text: power ? "On" : "Off"
                checked: power
                enabled: online
                onToggled: deviceManager.togglePower(deviceId)
            }
        }

        // Type-specific controls
        Loader {
            Layout.fillWidth: true
            sourceComponent: type === "light" ? lightControls : (type === "thermostat" ? thermostatControls : undefined)
        }

        // Footer
        RowLayout {
            Layout.fillWidth: true
            spacing: 12
            Label {
                Layout.fillWidth: true
                color: "#555"
                text: type === "light" ? `Brightness: ${brightness}%` : (type === "thermostat" ? `Temp: ${temperature.toFixed(1)}°C` : (type === "plug" ? (power ? "Powered" : "Idle") : type))
            }
            Button {
                text: power ? "Turn Off" : "Turn On"
                enabled: online
                onClicked: deviceManager.togglePower(deviceId)
            }
        }
    }

    Component {
        id: lightControls
        RowLayout {
            spacing: 8
            Label { text: "Brightness" }
            Slider {
                id: slider
                from: 0; to: 100; stepSize: 1
                value: brightness
                enabled: online && power
                onMoved: deviceManager.setBrightness(deviceId, Math.round(value))
            }
            Label { text: `${Math.round(slider.value)}%` }
        }
    }

    Component {
        id: thermostatControls
        RowLayout {
            spacing: 8
            Label { text: "Set Temp" }
            Slider {
                id: tslider
                from: 16; to: 28; stepSize: 0.5
                value: temperature
                enabled: online
                onMoved: deviceManager.setTemperature(deviceId, value)
            }
            Label { text: `${tslider.value.toFixed(1)}°C` }
        }
    }
}
