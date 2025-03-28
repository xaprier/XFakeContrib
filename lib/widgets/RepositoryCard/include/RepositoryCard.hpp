#ifndef REPOSITORYCARD_HPP
#define REPOSITORYCARD_HPP

#include <QPointer>
#include <QWidget>

#include "RepositoryCardConnections.hpp"
#include "RepositoryTableView.hpp"
#include "Settings.hpp"

namespace Ui {
class RepositoryCardUI;
}

class RepositoryCard final : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCard)
  public:
    RepositoryCard(QWidget *parent = nullptr);
    ~RepositoryCard() final;

    QIcon GetIcon() const { return QIcon(); }
    QString GetName() const { return QObject::tr("Repositories"); }

    QPointer<RepositoryCardConnections> GetConnections() const { return m_Connections; }

  private:
    mutable QPointer<RepositoryCardConnections> m_Connections;
    QPointer<RepositoryTableView> m_Repositories;
    Settings &m_Settings;
    Ui::RepositoryCardUI *m_Ui;
};

#endif  // REPOSITORYCARD_HPP