#pragma once

#include <QAbstractListModel>
#include <QVariantMap>
#include "devicemanager.h"

class DevicesModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString roomFilter READ roomFilter WRITE setRoomFilter NOTIFY roomFilterChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        RoomRole,
        TypeRole,
        OnlineRole,
        PowerRole,
        BrightnessRole,
        TemperatureRole
    };

    explicit DevicesModel(DeviceManager* manager, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString roomFilter() const { return m_roomFilter; }
    void setRoomFilter(const QString& room);

    Q_INVOKABLE QVariantMap get(int row) const;

public slots:
    void refresh();
    void onDeviceUpdated(int id);

signals:
    void roomFilterChanged();

private:
    const Device* deviceAtFiltered(int row) const;
    QList<int> filteredIndexes() const;

    DeviceManager* m_manager;
    QString m_roomFilter;
};
