#pragma once

#include <QObject>
#include <QVector>
#include <QString>
#include <QTimer>

struct Device {
    int id = -1;
    QString name;
    QString room;
    QString type; // light, thermostat, plug, camera
    bool online = true;
    bool power = false;
    int brightness = 0; // 0-100 for lights
    double temperature = 22.0; // for thermostats
};

class DeviceManager : public QObject {
    Q_OBJECT
public:
    explicit DeviceManager(QObject* parent = nullptr);

    const QVector<Device>& devices() const { return m_devices; }

    Q_INVOKABLE void togglePower(int id);
    Q_INVOKABLE void setBrightness(int id, int value);
    Q_INVOKABLE void setTemperature(int id, double value);

signals:
    void devicesChanged();
    void deviceUpdated(int id);

private slots:
    void simulateChanges();

private:
    QVector<Device> m_devices;
    QTimer m_simTimer;
};
