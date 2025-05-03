#ifndef CONTRIBCARD_HPP
#define CONTRIBCARD_HPP

#include <QDate>
#include <QGridLayout>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include <map>

#include "Card.hpp"
#include "Contrib.hpp"
#include "ContribTotal.hpp"
#include "ContributionPeriod.hpp"
#include "Icon.hpp"
#include "LevelColorIndicator.hpp"
#include "YearContrib.hpp"
#include "YearContribTotalIndicator.hpp"
#include "XFakeContribHelper.hpp"

#include "Widgets_Global.hpp"

class WIDGETS_EXPORT ContribCard : public Card {
    Q_OBJECT
  public:
    ContribCard(QWidget* parent = nullptr);
    ContribCard(const std::map<QDate, Contrib>& allContribs, QWidget* parent = nullptr);
    ~ContribCard();
    void Update(const std::map<QDate, Contrib>& allContribs);

    virtual Icon GetIcon() const override { return Icon(""); }
    virtual QString GetName() const override { return QObject::tr("Contributions"); }
    virtual void UpdateIcons() override;
    virtual void Update() override {}

  private:
    void _UpdateContribs(const std::map<QDate, Contrib>& allContribs);
    void _UpdateTotalContribs(const std::map<int, ContribTotal>& allTotalContribs);
    void _UpdateFirstContrib(const QDate& firstContrib);
    void _SetupUI();
    void _CreateConnections();

  signals:
    void si_Reload();
    void si_SetStartDate(QDate date);
    void si_SetEndDate(QDate date);

  private slots:
    void sl_OnContributionPeriodChanged(int index);
    void sl_LeftClickedToDay(QDate date);
    void sl_RightClickedToDay(QDate date);
    void sl_MiddleClickedToDay(QDate date);
    void sl_InfoButtonClicked();

  private:
    QSharedPointer<QToolButton> m_ReloadButton, m_InfoButton;
    QSharedPointer<ContributionPeriod> m_ContributionPeriod;
    QSharedPointer<YearContrib> m_YearContribWidget;
    QSharedPointer<LevelColorIndicator> m_Indicator;
    QSharedPointer<YearContribTotalIndicator> m_TotalContribWidget;
    std::map<QDate, Contrib> m_Contribs;
    std::map<int, ContribTotal> m_TotalContribs;
    QDate m_FirstContribDate;
};

#endif  // CONTRIBCARD_HPP