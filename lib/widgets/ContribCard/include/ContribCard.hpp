#ifndef CONTRIBCARD_HPP
#define CONTRIBCARD_HPP

#include <QDate>
#include <QGridLayout>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include <map>

#include "Contrib.hpp"
#include "ContribTotal.hpp"
#include "ContributionPeriod.hpp"
#include "Icon.hpp"
#include "LevelColorIndicator.hpp"
#include "YearContrib.hpp"
#include "YearContribTotalIndicator.hpp"

class ContribCard : public QWidget {
    Q_OBJECT

  public:
    ContribCard(QWidget* parent = nullptr) {
        this->_SetupUI();
        this->_CreateConnections();
    }
    ContribCard(const std::map<QDate, Contrib>& allContribs, QWidget* parent = nullptr);
    void Update(const std::map<QDate, Contrib>& allContribs = {});

    Icon GetIcon() const { return Icon(":/icons/contributions.svg"); }
    QString GetName() const { return QObject::tr("Contributions"); }

  private:
    void _UpdateContribs(const std::map<QDate, Contrib>& allContribs);
    void _UpdateTotalContribs(const std::map<int, ContribTotal>& allTotalContribs);
    void _UpdateFirstContrib(const QDate& firstContrib);
    void _SetupUI();
    void _CreateConnections();

  signals:
    void si_Reload();

  private slots:
    void sl_OnContributionPeriodChanged(int index);

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