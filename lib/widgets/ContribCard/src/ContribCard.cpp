#include "ContribCard.hpp"

#include "Icon.hpp"
#include "XFakeContribHelper.hpp"

ContribCard::ContribCard(QWidget* parent) : Card(parent) {
    this->_SetupUI();
    this->_CreateConnections();
}

ContribCard::ContribCard(const std::map<QDate, Contrib>& allContribs, QWidget* parent) : ContribCard(parent) {
    m_Contribs = allContribs;
    this->Update(allContribs);
}

ContribCard::~ContribCard() {
    qDebug() << "ContribCard destructor called";
}

void ContribCard::Update(const std::map<QDate, Contrib>& allContribs) {
    this->_UpdateContribs(allContribs);
}

void ContribCard::UpdateIcons() {
    m_InfoButton->setIcon(Icon(":/icons/info.svg"));
    m_ReloadButton->setIcon(Icon(":/icons/reload.svg"));
    this->sl_OnContributionPeriodChanged(m_ContributionPeriod->currentIndex());
    this->m_Indicator->UpdateColors();
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

    // todo: info button will show how to use contribcard with committer(left click start date, right click end date, middle both)
    m_InfoButton = QSharedPointer<QToolButton>::create(this);
    layout->addWidget(m_InfoButton.get(), 0, 0, 1, 1);
    m_InfoButton->setIcon(Icon(":/icons/info.svg"));

    m_ReloadButton = QSharedPointer<QToolButton>::create(this);
    layout->addWidget(m_ReloadButton.get(), 0, 1, 1, 1);
    m_ReloadButton->setIcon(Icon(":/icons/reload.svg"));

    m_ContributionPeriod = QSharedPointer<ContributionPeriod>::create(this);
    layout->addWidget(m_ContributionPeriod.get(), 0, 2, 1, 1);

    m_Indicator = QSharedPointer<LevelColorIndicator>::create(this);
    layout->addWidget(m_Indicator.get(), 0, 10, 1, 2);

    m_YearContribWidget = QSharedPointer<YearContrib>::create(this);
    layout->addWidget(m_YearContribWidget.get(), 1, 0, 1, 12);

    m_TotalContribWidget = QSharedPointer<YearContribTotalIndicator>::create();
    layout->addWidget(m_TotalContribWidget.get(), 0, 3, 1, 1);

    setLayout(layout);
}

void ContribCard::_CreateConnections() {
    // Connect the signal to the slot that will handle the selection change
    connect(m_ContributionPeriod.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContribCard::sl_OnContributionPeriodChanged);
    connect(m_ContributionPeriod.get(), &QComboBox::currentTextChanged, m_TotalContribWidget.get(), [&](const QString& currentText) {
        this->_UpdateTotalContribs(m_TotalContribs);
    });
    connect(m_ReloadButton.get(), &QToolButton::clicked, this, [this]() {
        emit si_Reload();
    });

    for (auto monthContrib : m_YearContribWidget->GetMonthContribs()) {
        auto dayContribs = monthContrib.lock()->GetDayContribs();
        for (auto dayContrib : dayContribs) {
            connect(dayContrib.lock().get(), &DayContrib::si_LeftClicked, this, &ContribCard::sl_LeftClickedToDay);
            connect(dayContrib.lock().get(), &DayContrib::si_RightClicked, this, &ContribCard::sl_RightClickedToDay);
            connect(dayContrib.lock().get(), &DayContrib::si_MiddleClicked, this, &ContribCard::sl_MiddleClickedToDay);
        }
    }
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

    // Remove the connections between day contrib click signals
    for (auto monthContrib : m_YearContribWidget->GetMonthContribs()) {
        auto dayContribs = monthContrib.lock()->GetDayContribs();
        for (auto dayContrib : dayContribs) {
            disconnect(dayContrib.lock().get(), &DayContrib::si_LeftClicked, this, &ContribCard::sl_LeftClickedToDay);
            disconnect(dayContrib.lock().get(), &DayContrib::si_RightClicked, this, &ContribCard::sl_RightClickedToDay);
            disconnect(dayContrib.lock().get(), &DayContrib::si_MiddleClicked, this, &ContribCard::sl_MiddleClickedToDay);
        }
    }

    m_YearContribWidget->Update(selectedItem, m_Contribs, endDate);

    // Create the connections between day contrib click signals
    for (auto monthContrib : m_YearContribWidget->GetMonthContribs()) {
        auto dayContribs = monthContrib.lock()->GetDayContribs();
        for (auto dayContrib : dayContribs) {
            connect(dayContrib.lock().get(), &DayContrib::si_LeftClicked, this, &ContribCard::sl_LeftClickedToDay);
            connect(dayContrib.lock().get(), &DayContrib::si_RightClicked, this, &ContribCard::sl_RightClickedToDay);
            connect(dayContrib.lock().get(), &DayContrib::si_MiddleClicked, this, &ContribCard::sl_MiddleClickedToDay);
        }
    }
}

void ContribCard::sl_LeftClickedToDay(const QDate& date) {
    emit this->si_SetStartDate(date);
}

void ContribCard::sl_RightClickedToDay(const QDate& date) {
    emit this->si_SetEndDate(date);
}

void ContribCard::sl_MiddleClickedToDay(const QDate& date) {
    emit this->si_SetStartDate(date);
    emit this->si_SetEndDate(date);
}
