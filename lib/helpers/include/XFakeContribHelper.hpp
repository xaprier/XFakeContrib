#ifndef XFAKECONTRIBHELPER_HPP
#define XFAKECONTRIBHELPER_HPP

#include <Contrib.hpp>
#include <ContribTotal.hpp>
#include <QDate>
#include <QObject>
#include <map>
namespace XFakeContribHelper {
void GetTotalContribs(std::map<int, ContribTotal>& getItem, const std::map<QDate, Contrib> allContribs = {});
void GetFirstContrib(Contrib& getItem, const std::map<QDate, Contrib>& allContribs = {});
void GetFirstContrib(QDate& getItem, const std::map<QDate, Contrib>& allContribs = {});
template <typename Signal, typename Slot>
void safeConnect(QObject* sender, Signal signal, QObject* receiver, Slot slot, const QString& name);
}  // namespace XFakeContribHelper

#endif  // XFAKECONTRIBHELPER_HPP