#include "XFakeContribHelper.hpp"

#include <QDebug>

#include "ContribTotal.hpp"

namespace XFakeContribHelper {
void GetTotalContribs(std::map<int, ContribTotal>& getItem, const std::map<QDate, Contrib> allContribs) {
    ContribTotal lastYear(0, 0);
    for (const auto& [date, contrib] : allContribs) {
        int currentCount = contrib.GetCount();
        int currentLevel = contrib.GetLevel();
        QDate currentDAte = contrib.GetDate();
        getItem[date.year()] = ContribTotal(getItem[date.year()].GetCount() + contrib.GetCount(), date.year());
        if (QDate::currentDate().addYears(-1) < date && QDate::currentDate() >= date)
            lastYear.SetCount(lastYear.GetCount() + currentCount);
    }
    getItem[0] = lastYear;
}

void GetFirstContrib(Contrib& getItem, const std::map<QDate, Contrib>& allContribs) {
    if (!allContribs.empty()) {
        // Initialize with a very large date for comparison.
        QDate earliestDate = QDate::fromString("9999-12-31", "yyyy-MM-dd");
        Contrib earliestContrib;
        for (const auto& entry : allContribs) {
            if (entry.first < earliestDate) {
                earliestDate = entry.first;
                earliestContrib = entry.second;
            }
        }

        getItem = earliestContrib;
    } else
        getItem = Contrib();
}

void GetFirstContrib(QDate& getItem, const std::map<QDate, Contrib>& allContribs) {
    if (!allContribs.empty()) {
        // Initialize with a very large date for comparison.
        QDate earliestDate = QDate::fromString("9999-12-31", "yyyy-MM-dd");

        for (const auto& entry : allContribs) {
            if (entry.first < earliestDate) {
                earliestDate = entry.first;
            }
        }

        getItem = earliestDate;
    } else
        getItem = QDate::currentDate();
}

template <typename Signal, typename Slot>
void safeConnect(QObject* sender, Signal signal, QObject* receiver, Slot slot, const QString& name) {
    if (sender && receiver) {
        QObject::connect(sender, signal, receiver, slot);
    } else {
        qWarning() << "Failed to connect signal for" << name;
    }
}
}  // namespace XFakeContribHelper