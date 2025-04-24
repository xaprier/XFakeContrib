#ifndef XFAKECONTRIBHELPER_HPP
#define XFAKECONTRIBHELPER_HPP

#include <Contrib.hpp>
#include <ContribTotal.hpp>
#include <QDate>
#include <QDebug>
#include <QObject>
#include <map>

namespace XFakeContribHelper {
void GetTotalContribs(std::map<int, ContribTotal>& getItem, const std::map<QDate, Contrib> allContribs = {});
void GetFirstContrib(Contrib& getItem, const std::map<QDate, Contrib>& allContribs = {});
void GetFirstContrib(QDate& getItem, const std::map<QDate, Contrib>& allContribs = {});
template <typename Sender, typename Signal, typename Receiver, typename Slot>
bool safeConnect(Sender* sender, Signal signal, Receiver* receiver, Slot slot, const QString& name = "", Qt::ConnectionType type = Qt::AutoConnection) {
    // Check if sender and receiver are QObject-derived types
    static_assert(std::is_base_of<QObject, Sender>::value, "Sender must be a QObject-derived class.");
    static_assert(std::is_base_of<QObject, Receiver>::value, "Receiver must be a QObject-derived class.");

    if (!QObject::connect(sender, signal, receiver, slot, type)) {
        qWarning() << "Failed to connect signal-slot:" << name;
        return false;
    }
    return true;
}
}  // namespace XFakeContribHelper

#endif  // XFAKECONTRIBHELPER_HPP