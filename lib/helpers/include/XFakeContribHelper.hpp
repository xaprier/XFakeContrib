#ifndef XFAKECONTRIBHELPER_HPP
#define XFAKECONTRIBHELPER_HPP

#include <Contrib.hpp>
#include <ContribTotal.hpp>
#include <QDate>
#include <map>
namespace XFakeContribHelper {
void GetTotalContribs(std::map<int, ContribTotal>& getItem, const std::map<QDate, Contrib> allContribs = {});
void GetFirstContrib(Contrib& getItem, const std::map<QDate, Contrib>& allContribs = {});
void GetFirstContrib(QDate& getItem, const std::map<QDate, Contrib>& allContribs = {});
}  // namespace XFakeContribHelper

#endif  // XFAKECONTRIBHELPER_HPP