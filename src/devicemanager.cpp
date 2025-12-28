#include "devicemanager.h"
#include <QtGlobal>
#include <QRandomGenerator>

DeviceManager::DeviceManager(QObject* parent)
    : QObject(parent)
{
    // Seed demo devices
    m_devices = {
        {1, QStringLiteral("Living Light"), QStringLiteral("Living Room"), QStringLiteral("light"), true, true, 75, 22.0},
        {2, QStringLiteral("Hall Thermostat"), QStringLiteral("Hall"), QStringLiteral("thermostat"), true, false, 0, 21.5},
        {3, QStringLiteral("Kitchen Plug"), QStringLiteral("Kitchen"), QStringLiteral("plug"), true, false, 0, 0.0},
        {4, QStringLiteral("Bedroom Lamp"), QStringLiteral("Bedroom"), QStringLiteral("light"), true, true, 40, 0.0},
        {5, QStringLiteral("Garage Camera"), QStringLiteral("Garage"), QStringLiteral("camera"), true, true, 0, 0.0}
    };

    connect(&m_simTimer, &QTimer::timeout, this, &DeviceManager::simulateChanges);
    m_simTimer.start(3000);
}

void DeviceManager::togglePower(int id)
{
    for (auto &d : m_devices) {
        if (d.id == id) {
            d.power = !d.power;
            emit deviceUpdated(id);
            emit devicesChanged();
            return;
        }
    }
}

void DeviceManager::setBrightness(int id, int value)
{
    for (auto &d : m_devices) {
        if (d.id == id && d.type == QStringLiteral("light")) {
            d.brightness = qBound(0, value, 100);
            emit deviceUpdated(id);
            emit devicesChanged();
            return;
        }
    }
}

void DeviceManager::setTemperature(int id, double value)
{
    for (auto &d : m_devices) {
        if (d.id == id && d.type == QStringLiteral("thermostat")) {
            d.temperature = value;
            emit deviceUpdated(id);
            emit devicesChanged();
            return;
        }
    }
}

void DeviceManager::simulateChanges()
{
    if (m_devices.isEmpty()) return;
    int idx = QRandomGenerator::global()->bounded(m_devices.size());
    Device &d = m_devices[idx];
    // Randomly flip online or tweak value to simulate updates
    int action = QRandomGenerator::global()->bounded(3);
    if (action == 0) {
        d.online = !d.online;
    } else if (action == 1 && d.type == QStringLiteral("light")) {
        int delta = QRandomGenerator::global()->bounded(-10, 11);
        d.brightness = qBound(0, d.brightness + delta, 100);
    } else if (action == 2 && d.type == QStringLiteral("thermostat")) {
        double delta = QRandomGenerator::global()->bounded(-5, 6) / 10.0; // +-0.5C
        d.temperature += delta;
    }
    emit deviceUpdated(d.id);
    emit devicesChanged();
}
