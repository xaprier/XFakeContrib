#ifndef CONTRIBCARD_HPP
#define CONTRIBCARD_HPP

#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#include "Contrib.hpp"
#include "ContributionPeriod.hpp"
#include "LevelColorIndicator.hpp"
#include "YearContrib.hpp"

class ContribCard : public QWidget {
    Q_OBJECT

  public:
    ContribCard(const std::vector<Contrib>& allContribs, QDate firstContrib = QDate::currentDate(), QWidget* parent = nullptr) : QWidget(parent), m_Contribs(allContribs) {
        // Layout for the main widget
        QGridLayout* layout = new QGridLayout(this);

        // Create the ContributionPeriod combo box
        m_ContributionPeriod = new ContributionPeriod(firstContrib, this);
        layout->addWidget(m_ContributionPeriod, 0, 0, 1, 1);

        m_Indicator = new LevelColorIndicator(this);
        layout->addWidget(m_Indicator, 0, 10, 1, 2);

        m_YearContribWidget = new YearContrib(m_ContributionPeriod->currentText(), allContribs, QDate::currentDate(), this);
        layout->addWidget(m_YearContribWidget, 1, 0, 1, 12);

        // Connect the signal to the slot that will handle the selection change
        connect(m_ContributionPeriod, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContribCard::onContributionPeriodChanged);
        setLayout(layout);
    }

    void updateContribs(const std::vector<Contrib>& allContribs) {
        this->m_Contribs = allContribs;

        // update the yearContrib with signal
        emit m_ContributionPeriod->currentIndexChanged(m_ContributionPeriod->currentIndex());
    }

  private slots:
    void onContributionPeriodChanged(int index) {
        QString selectedItem = m_ContributionPeriod->itemText(index);

        // Delete the previous YearContrib widget if exists
        if (m_YearContribWidget) {
            delete m_YearContribWidget;
            m_YearContribWidget = nullptr;
        }

        // Create a new YearContrib based on the selected item
        if (selectedItem == "Last 12 Months") {
            QDate endDate = QDate::currentDate();
            m_YearContribWidget = new YearContrib(selectedItem, m_Contribs, endDate, this);
        } else {
            int selectedYear = selectedItem.toInt();
            QDate endDate = QDate(selectedYear, 12, 31);  // Set the date to 31/12/selectedYear
            m_YearContribWidget = new YearContrib(selectedItem, m_Contribs, endDate, this);
        }

        // Add the new YearContrib widget to the layout
        if (m_YearContribWidget) {
            static_cast<QGridLayout*>(layout())->addWidget(m_YearContribWidget, 1, 0, 1, 12);
        }
    }

  private:
    ContributionPeriod* m_ContributionPeriod;
    YearContrib* m_YearContribWidget;
    LevelColorIndicator* m_Indicator;
    std::vector<Contrib> m_Contribs;
};

#endif  // CONTRIBCARD_HPP