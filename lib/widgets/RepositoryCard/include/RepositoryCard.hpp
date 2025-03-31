#ifndef REPOSITORYCARD_HPP
#define REPOSITORYCARD_HPP

#include <QPointer>
#include <QWidget>

#include "Card.hpp"
#include "RepositoryCardConnections.hpp"
#include "RepositoryTableView.hpp"
#include "Settings.hpp"

namespace Ui {
class RepositoryCardUI;
}

class RepositoryCard final : public Card {
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

  private:
    mutable QPointer<RepositoryCardConnections> m_Connections;
    QPointer<RepositoryTableView> m_Repositories;
    Settings &m_Settings;
    Ui::RepositoryCardUI *m_Ui;
};

#endif  // REPOSITORYCARD_HPP