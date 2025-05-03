#ifndef CONTRIBUTIONPERIOD_HPP
#define CONTRIBUTIONPERIOD_HPP

#include <QComboBox>
#include <QDate>
#include <QString>

class ContributionPeriod : public QComboBox {
    Q_OBJECT
  public:
    /**
     * @brief Constructor for ContributionPeriod.
     *
     * Initializes the combobox with items representing the years from the firstContrib year
     * up to the current year, and includes a "Last 12 Months" option.
     *
     * @param firstContrib The date of the first contribution.
     * @param parent The parent widget (optional).
     */
    ContributionPeriod(QWidget* parent = nullptr, const QDate& firstContrib = QDate::currentDate())
        : QComboBox(parent) {
        this->UpdatePeriod(firstContrib);
    }

    void UpdatePeriod(const QDate& firstContrib = QDate::currentDate()) {
        // Clear combobox
        this->clear();

        // Get the year of the first contribution
        int startYear = firstContrib.year();

        // Get the current year
        int currentYear = QDate::currentDate().year();

        // Add "Last 12 Months" as the first item
        addItem(QObject::tr("Last 12 Months"));

        // Add items for each year from startYear to currentYear
        for (int year = currentYear; year >= startYear; --year) {
            addItem(QString::number(year));
        }
    }
};

#endif  // CONTRIBUTIONPERIOD_HPP
