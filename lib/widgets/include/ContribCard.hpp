#ifndef CONTRIBCARD_HPP
#define CONTRIBCARD_HPP

#include <qcombobox.h>
#include <qvariant.h>

#include <QDate>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <map>

#include "Contrib.hpp"
#include "ContribTotal.hpp"
#include "ContributionPeriod.hpp"
#include "LevelColorIndicator.hpp"
#include "YearContrib.hpp"
#include "YearContribTotalIndicator.hpp"

class ContribCard : public QWidget {
    Q_OBJECT

  public:
    ContribCard(const std::map<QDate, Contrib>& allContribs, const std::map<int, ContribTotal>& allTotalContribs, QDate firstContrib = QDate::currentDate(), QWidget* parent = nullptr) : QWidget(parent), m_Contribs(allContribs), m_TotalContribs(allTotalContribs) {
        // Layout for the main widget, this should raw data and will be deleted by Qt parent
        QGridLayout* layout = new QGridLayout(this);

        // Create the ContributionPeriod combo box
        m_ContributionPeriod = QSharedPointer<ContributionPeriod>::create(firstContrib, this);
        layout->addWidget(m_ContributionPeriod.get(), 0, 0, 1, 1);

        m_Indicator = QSharedPointer<LevelColorIndicator>::create(this);
        layout->addWidget(m_Indicator.get(), 0, 10, 1, 2);

        m_YearContribWidget = QSharedPointer<YearContrib>::create(m_ContributionPeriod->currentText(), allContribs, QDate::currentDate(), this);
        layout->addWidget(m_YearContribWidget.get(), 1, 0, 1, 12);

        int currentYear = m_ContributionPeriod->currentText().toInt();
        auto it = allTotalContribs.find(currentYear);
        int currentTotal = 0;
        if (it != allTotalContribs.end()) {
            currentTotal = it->second.getCount();
        }
        m_TotalContribWidget = QSharedPointer<YearContribTotalIndicator>::create(currentTotal);
        layout->addWidget(m_TotalContribWidget.get(), 0, 1, 1, 1);

        // Connect the signal to the slot that will handle the selection change
        connect(m_ContributionPeriod.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContribCard::onContributionPeriodChanged);
        connect(m_ContributionPeriod.get(), &QComboBox::currentTextChanged, m_TotalContribWidget.get(), [&](const QString& currentText) {
            /**
             * @brief if currentText is "Last 12 Months", toInt function will return 0
             * and also allTotalContribs holds last 12 months in key "0".
             */
            auto it = m_TotalContribs.find(currentText.toInt());
            if (it != m_TotalContribs.end())
                m_TotalContribWidget->setText(it->second.getCount());
        });
        setLayout(layout);
    }

    void updateContribs(const std::map<QDate, Contrib>& allContribs) {
        this->m_Contribs = allContribs;

        // update the yearContrib with signal
        emit m_ContributionPeriod->currentIndexChanged(m_ContributionPeriod->currentIndex());
    }

  private slots:
    void onContributionPeriodChanged(int index) {
        QString selectedItem = m_ContributionPeriod->itemText(index);

        // Delete the previous YearContrib widget if exists
        if (m_YearContribWidget) {
            m_YearContribWidget.reset();
        }

        // Create a new YearContrib based on the selected item
        if (selectedItem == "Last 12 Months") {
            QDate endDate = QDate::currentDate();
            m_YearContribWidget = QSharedPointer<YearContrib>::create(selectedItem, m_Contribs, endDate, this);
        } else {
            int selectedYear = selectedItem.toInt();
            QDate endDate = QDate(selectedYear, 12, 31);  // Set the date to 31/12/selectedYear
            m_YearContribWidget = QSharedPointer<YearContrib>::create(selectedItem, m_Contribs, endDate, this);
        }

        // Add the new YearContrib widget to the layout
        if (m_YearContribWidget) {
            static_cast<QGridLayout*>(layout())->addWidget(m_YearContribWidget.get(), 1, 0, 1, 12);
        }
    }

  private:
    QSharedPointer<ContributionPeriod> m_ContributionPeriod;
    QSharedPointer<YearContrib> m_YearContribWidget;
    QSharedPointer<LevelColorIndicator> m_Indicator;
    QSharedPointer<YearContribTotalIndicator> m_TotalContribWidget;
    std::map<QDate, Contrib> m_Contribs;
    std::map<int, ContribTotal> m_TotalContribs;
};

#endif  // CONTRIBCARD_HPP