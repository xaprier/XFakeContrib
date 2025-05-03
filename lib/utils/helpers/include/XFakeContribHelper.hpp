#ifndef XFAKECONTRIBHELPER_HPP
#define XFAKECONTRIBHELPER_HPP

#include <Contrib.hpp>
#include <ContribTotal.hpp>
#include <QDate>
#include <QObject>
#include <map>

#include "Logger.hpp"

#include "Utils_Global.hpp"

namespace XFakeContribHelper {

void UTILS_EXPORT GetTotalContribs(std::map<int, ContribTotal>& getItem, const std::map<QDate, Contrib> allContribs = {});
void UTILS_EXPORT GetFirstContrib(Contrib& getItem, const std::map<QDate, Contrib>& allContribs = {});
void UTILS_EXPORT GetFirstContrib(QDate& getItem, const std::map<QDate, Contrib>& allContribs = {});

template <typename Sender, typename Signal, typename Receiver, typename Slot>
inline bool safeConnect(Sender* sender, Signal signal, Receiver* receiver, Slot slot, const QString& name = "", Qt::ConnectionType type = Qt::AutoConnection) {
    // Check if sender and receiver are QObject-derived types
    static_assert(std::is_base_of<QObject, Sender>::value, "Sender must be a QObject-derived class.");
    static_assert(std::is_base_of<QObject, Receiver>::value, "Receiver must be a QObject-derived class.");

    if (!QObject::connect(sender, signal, receiver, slot, type)) {
        Logger::log_static(QObject::tr("Failed to connect signal to slot: %1").arg(name).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return false;
    }
    return true;
}

}  // namespace XFakeContribHelper

#endif  // XFAKECONTRIBHELPER_HPP