#ifndef CONTRIBCARD_HPP
#define CONTRIBCARD_HPP

#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#include "ContributionPeriod.hpp"
#include "YearContrib.hpp"

class ContribCard : public QWidget {
    Q_OBJECT

  public:
    ContribCard(const std::vector<int>& allContribs, const std::vector<int>& allLevels, QDate firstContrib = QDate::currentDate(), QWidget* parent = nullptr) : QWidget(parent), m_Contribs(allContribs), m_Levels(allLevels) {
        // Layout for the main widget
        QVBoxLayout* layout = new QVBoxLayout(this);

        // Create the ContributionPeriod combo box
        contributionPeriod = std::make_shared<ContributionPeriod>(firstContrib, this);
        layout->addWidget(contributionPeriod.get());

        yearContribWidget = std::make_shared<YearContrib>(contributionPeriod->currentText(), allContribs, allLevels);
        layout->addWidget(yearContribWidget.get());

        // Connect the signal to the slot that will handle the selection change
        connect(contributionPeriod.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContribCard::onContributionPeriodChanged);
        setLayout(layout);
    }

    void updateContribs(const std::vector<int>& allContribs, const std::vector<int>& allLevels) {
        this->m_Contribs = allContribs;
        this->m_Levels = allLevels;
        // update the yearContrib with signal
        emit contributionPeriod->currentIndexChanged(contributionPeriod->currentIndex());
    }

  private slots:
    void onContributionPeriodChanged(int index) {
        QString selectedItem = contributionPeriod->itemText(index);

        // Delete the previous YearContrib widget if exists
        if (yearContribWidget.get()) {
            yearContribWidget.reset();
        }

        // Create a new YearContrib based on the selected item
        if (selectedItem == "Last 12 Months") {
            QDate endDate = QDate::currentDate();
            yearContribWidget = std::make_shared<YearContrib>(selectedItem, m_Contribs, m_Levels, endDate, this);
        } else {
            int selectedYear = selectedItem.toInt();
            QDate endDate = QDate(selectedYear, 12, 31);  // Set the date to 31/12/selectedYear
            yearContribWidget = std::make_shared<YearContrib>(selectedItem, m_Contribs, m_Levels, endDate, this);
        }

        // Add the new YearContrib widget to the layout
        if (yearContribWidget) {
            static_cast<QVBoxLayout*>(layout())->addWidget(yearContribWidget.get());
        }
    }

  private:
    std::shared_ptr<ContributionPeriod> contributionPeriod;
    std::shared_ptr<YearContrib> yearContribWidget;
    std::vector<int> m_Contribs, m_Levels;
};

#endif  // CONTRIBCARD_HPP