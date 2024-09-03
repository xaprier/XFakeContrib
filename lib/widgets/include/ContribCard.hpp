#ifndef CONTRIBCARD_HPP
#define CONTRIBCARD_HPP

#include <qgridlayout.h>

#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#include "ContributionPeriod.hpp"
#include "LevelColorIndicator.hpp"
#include "YearContrib.hpp"

class ContribCard : public QWidget {
    Q_OBJECT

  public:
    ContribCard(const std::vector<int>& allContribs, const std::vector<int>& allLevels, QDate firstContrib = QDate::currentDate(), QWidget* parent = nullptr) : QWidget(parent), m_Contribs(allContribs), m_Levels(allLevels) {
        // Layout for the main widget
        QGridLayout* layout = new QGridLayout(this);

        // Create the ContributionPeriod combo box
        m_ContributionPeriod = std::make_shared<ContributionPeriod>(firstContrib, this);
        layout->addWidget(m_ContributionPeriod.get(), 0, 0, 1, 1);

        m_Indicator = std::make_shared<LevelColorIndicator>(this);
        layout->addWidget(m_Indicator.get(), 0, 10, 1, 2);

        m_YearContribWidget = std::make_shared<YearContrib>(m_ContributionPeriod->currentText(), allContribs, allLevels);
        layout->addWidget(m_YearContribWidget.get(), 1, 0, 1, 12);

        // Connect the signal to the slot that will handle the selection change
        connect(m_ContributionPeriod.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContribCard::onContributionPeriodChanged);
        setLayout(layout);
    }

    void updateContribs(const std::vector<int>& allContribs, const std::vector<int>& allLevels) {
        this->m_Contribs = allContribs;
        this->m_Levels = allLevels;
        // update the yearContrib with signal
        emit m_ContributionPeriod->currentIndexChanged(m_ContributionPeriod->currentIndex());
    }

  private slots:
    void onContributionPeriodChanged(int index) {
        QString selectedItem = m_ContributionPeriod->itemText(index);

        // Delete the previous YearContrib widget if exists
        if (m_YearContribWidget.get()) {
            m_YearContribWidget.reset();
        }

        // Create a new YearContrib based on the selected item
        if (selectedItem == "Last 12 Months") {
            QDate endDate = QDate::currentDate();
            m_YearContribWidget = std::make_shared<YearContrib>(selectedItem, m_Contribs, m_Levels, endDate, this);
        } else {
            int selectedYear = selectedItem.toInt();
            QDate endDate = QDate(selectedYear, 12, 31);  // Set the date to 31/12/selectedYear
            m_YearContribWidget = std::make_shared<YearContrib>(selectedItem, m_Contribs, m_Levels, endDate, this);
        }

        // Add the new YearContrib widget to the layout
        if (m_YearContribWidget) {
            static_cast<QGridLayout*>(layout())->addWidget(m_YearContribWidget.get(), 1, 0, 1, 12);
        }
    }

  private:
    std::shared_ptr<ContributionPeriod> m_ContributionPeriod;
    std::shared_ptr<YearContrib> m_YearContribWidget;
    std::shared_ptr<LevelColorIndicator> m_Indicator;
    std::vector<int> m_Contribs, m_Levels;
};

#endif  // CONTRIBCARD_HPP