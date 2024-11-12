#include "ContribCard.hpp"

#include "XFakeContribHelper.hpp"

ContribCard::ContribCard(
    const std::map<QDate, Contrib>& allContribs,
    QWidget* parent) : QWidget(parent), m_Contribs(allContribs) {
    this->_SetupUI();
    this->_CreateConnections();
    this->Update(allContribs);
}

void ContribCard::Update(const std::map<QDate, Contrib>& allContribs) {
    this->_UpdateContribs(allContribs);
}

void ContribCard::_UpdateContribs(const std::map<QDate, Contrib>& allContribs) {
    this->m_Contribs = allContribs;

    XFakeContribHelper::GetTotalContribs(m_TotalContribs, allContribs);
    XFakeContribHelper::GetFirstContrib(m_FirstContribDate, allContribs);
    this->_UpdateTotalContribs(m_TotalContribs);
    this->m_ContributionPeriod->blockSignals(true);  // m_ContributionPeriod combobox clear will create a loop if we dont disable connection
    this->_UpdateFirstContrib(m_FirstContribDate);
    this->m_ContributionPeriod->blockSignals(false);

    // update the yearContrib with signal
    emit m_ContributionPeriod->currentIndexChanged(m_ContributionPeriod->currentIndex());
}

void ContribCard::_UpdateTotalContribs(const std::map<int, ContribTotal>& allTotalContribs) {
    QString selectedItem = m_ContributionPeriod->currentText();
    /**
     * @brief if currentText is "Last 12 Months", toInt function will return 0
     * and also allTotalContribs holds last 12 months in key "0".
     */
    int currentYear = m_ContributionPeriod->currentText().toInt();
    auto it = allTotalContribs.find(currentYear);
    int currentTotal = 0;
    if (it != allTotalContribs.end()) {
        currentTotal = it->second.GetCount();
    }
    m_TotalContribWidget->SetText(currentTotal);
}

void ContribCard::_UpdateFirstContrib(const QDate& firstContrib) {
    m_ContributionPeriod->UpdatePeriod(firstContrib);
}

void ContribCard::_SetupUI() {
    // Layout for the main widget, this should raw data and will be deleted by Qt parent
    QGridLayout* layout = new QGridLayout(this);

    // Create the ContributionPeriod combo box
    m_ContributionPeriod = QSharedPointer<ContributionPeriod>::create(this);
    layout->addWidget(m_ContributionPeriod.get(), 0, 0, 1, 1);

    m_Indicator = QSharedPointer<LevelColorIndicator>::create(this);
    layout->addWidget(m_Indicator.get(), 0, 10, 1, 2);

    m_YearContribWidget = QSharedPointer<YearContrib>::create(this);
    layout->addWidget(m_YearContribWidget.get(), 1, 0, 1, 12);

    m_TotalContribWidget = QSharedPointer<YearContribTotalIndicator>::create();
    layout->addWidget(m_TotalContribWidget.get(), 0, 1, 1, 1);
    setLayout(layout);
}

void ContribCard::_CreateConnections() {
    // Connect the signal to the slot that will handle the selection change
    connect(m_ContributionPeriod.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContribCard::sl_OnContributionPeriodChanged);
    connect(m_ContributionPeriod.get(), &QComboBox::currentTextChanged, m_TotalContribWidget.get(), [&](const QString& currentText) {
        this->_UpdateTotalContribs(m_TotalContribs);
    });
}

void ContribCard::sl_OnContributionPeriodChanged(int index) {
    QString selectedItem = m_ContributionPeriod->itemText(index);

    // Create a new YearContrib based on the selected item
    QDate endDate;
    if (selectedItem == "Last 12 Months") {
        endDate = QDate::currentDate();
    } else {
        int selectedYear = selectedItem.toInt();
        endDate = QDate(selectedYear, 12, 31);  // Set the date to 31/12/selectedYear
    }
    m_YearContribWidget->Update(selectedItem, m_Contribs, endDate);
}