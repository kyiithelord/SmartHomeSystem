#include "devicesmodel.h"
#include <algorithm>

DevicesModel::DevicesModel(DeviceManager* manager, QObject* parent)
    : QAbstractListModel(parent)
    , m_manager(manager)
{
    Q_ASSERT(m_manager);
    connect(m_manager, &DeviceManager::devicesChanged, this, &DevicesModel::refresh);
    connect(m_manager, &DeviceManager::deviceUpdated, this, &DevicesModel::onDeviceUpdated);
}

int DevicesModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return filteredIndexes().size();
}

QVariant DevicesModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return {};
    const Device* d = deviceAtFiltered(index.row());
    if (!d) return {};

    switch (role) {
    case IdRole: return d->id;
    case NameRole: return d->name;
    case RoomRole: return d->room;
    case TypeRole: return d->type;
    case OnlineRole: return d->online;
    case PowerRole: return d->power;
    case BrightnessRole: return d->brightness;
    case TemperatureRole: return d->temperature;
    default: return {};
    }
}

QHash<int, QByteArray> DevicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[RoomRole] = "room";
    roles[TypeRole] = "type";
    roles[OnlineRole] = "online";
    roles[PowerRole] = "power";
    roles[BrightnessRole] = "brightness";
    roles[TemperatureRole] = "temperature";
    return roles;
}

void DevicesModel::setRoomFilter(const QString& room)
{
    if (m_roomFilter == room)
        return;
    beginResetModel();
    m_roomFilter = room;
    endResetModel();
    emit roomFilterChanged();
}

QVariantMap DevicesModel::get(int row) const
{
    QVariantMap map;
    const Device* d = deviceAtFiltered(row);
    if (!d)
        return map;
    map["id"] = d->id;
    map["name"] = d->name;
    map["room"] = d->room;
    map["type"] = d->type;
    map["online"] = d->online;
    map["power"] = d->power;
    map["brightness"] = d->brightness;
    map["temperature"] = d->temperature;
    return map;
}

void DevicesModel::refresh()
{
    beginResetModel();
    endResetModel();
}

void DevicesModel::onDeviceUpdated(int /*id*/)
{
    // For simplicity we reset; could map row and emit dataChanged for better perf
    refresh();
}

const Device* DevicesModel::deviceAtFiltered(int row) const
{
    auto idxs = filteredIndexes();
    if (row < 0 || row >= idxs.size()) return nullptr;
    int realIdx = idxs.at(row);
    const auto& devices = m_manager->devices();
    if (realIdx < 0 || realIdx >= devices.size()) return nullptr;
    return &devices[realIdx];
}

QList<int> DevicesModel::filteredIndexes() const
{
    QList<int> idxs;
    const auto& devices = m_manager->devices();
    for (int i = 0; i < devices.size(); ++i) {
        if (m_roomFilter.isEmpty() || devices[i].room == m_roomFilter) {
            idxs.append(i);
        }
    }
    return idxs;
}
