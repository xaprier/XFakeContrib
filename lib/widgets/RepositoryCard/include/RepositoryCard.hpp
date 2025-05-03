#ifndef REPOSITORYCARD_HPP
#define REPOSITORYCARD_HPP

#include <QPointer>
#include <QWidget>

#include "Card.hpp"
#include "RepositoryCardConnections.hpp"
#include "RepositoryTableView.hpp"
#include "Settings.hpp"

#include "Widgets_Global.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class RepositoryCardUI;
}
QT_END_NAMESPACE

class WIDGETS_EXPORT RepositoryCard final : public Card {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCard)
  public:
    RepositoryCard(QWidget *parent = nullptr);
    ~RepositoryCard() final;

    virtual Icon GetIcon() const override { return Icon(":/icons/repository.svg"); }
    virtual QString GetName() const override { return QObject::tr("Repositories"); }

    virtual void UpdateIcons() override;
    virtual void Update() override {}

    QPointer<RepositoryCardConnections> GetConnections() const { return m_Connections; }

    void SetEndDate(const QDate &date);
    void SetStartDate(const QDate &date);

  private:
    mutable QPointer<RepositoryCardConnections> m_Connections;
    QPointer<RepositoryTableView> m_Repositories;
    Settings *m_Settings;
    Ui::RepositoryCardUI *m_Ui;
};

#endif  // REPOSITORYCARD_HPP