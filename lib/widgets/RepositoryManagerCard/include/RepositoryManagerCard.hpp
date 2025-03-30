#ifndef REPOSITORYMANAGERCARD_HPP
#define REPOSITORYMANAGERCARD_HPP

#include <qlistwidget.h>

#include <QListWidgetItem>
#include <QPointer>
#include <QWidget>

#include "GitRepository.hpp"
#include "Icon.hpp"
#include "RepositoryManagerComposedButton.hpp"
#include "Settings.hpp"

namespace Ui {
class RepositoryManagerCardUI;
}

class RepositoryManagerCard final : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryManagerCard)
  public:
    RepositoryManagerCard(QWidget *parent = nullptr);
    ~RepositoryManagerCard() final;

    Icon GetIcon() const { return Icon(":/icons/repository_manager.svg"); }
    QString GetName() const { return QObject::tr("Repository Manager"); }

  signals:
    void si_RepositoriesUpdated();

  private slots:
    void sl_RepositoryAddClicked(bool checked);
    void sl_RepositoryDeleteClicked(bool checked);
    void sl_RepositoryUpdateClicked(bool checked);

    void sl_BranchCreateClicked(bool checked);
    void sl_BranchDeleteClicked(bool checked);

    void sl_CurrentRowChangedForRepository(int row);

    void sl_ItemChangedForBranch(QListWidgetItem *item);

  private:
    void _SetupButtons();
    void _SetupConnections();
    void _LoadRepositories();
    void _LoadBranches();
    void _NoRepositoriesFound(bool yes);

  private:
    Ui::RepositoryManagerCardUI *m_Ui;
    QPointer<RepositoryManagerComposedButton> m_RepositoryDelete, m_RepositoryUpdate, m_RepositoryAdd;
    QPointer<RepositoryManagerComposedButton> m_BranchDelete, m_BranchUpdate, m_BranchCreate;
    Settings &m_Settings;
    QPointer<GitRepository> m_GitRepository;
    QStringList m_Repositories;
    QString m_OldBranch;
};

#endif  // REPOSITORYMANAGERCARD_HPP