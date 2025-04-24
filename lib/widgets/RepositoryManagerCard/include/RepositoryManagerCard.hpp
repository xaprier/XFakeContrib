#ifndef REPOSITORYMANAGERCARD_HPP
#define REPOSITORYMANAGERCARD_HPP

#include <qlistwidget.h>

#include <QListWidgetItem>
#include <QPointer>
#include <QWidget>

#include "Card.hpp"
#include "GitRepository.hpp"
#include "Icon.hpp"
#include "RepositoryManagerComposedAddButton.hpp"
#include "RepositoryManagerComposedDeleteButton.hpp"
#include "RepositoryManagerComposedUpdateButton.hpp"
#include "Settings.hpp"

namespace Ui {
class RepositoryManagerCardUI;
}

class RepositoryManagerCard final : public Card {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryManagerCard)
  public:
    RepositoryManagerCard(QWidget *parent = nullptr);
    ~RepositoryManagerCard() final;

    virtual Icon GetIcon() const override { return Icon(":/icons/branch.svg"); }
    virtual QString GetName() const override { return QObject::tr("Repository Manager"); }

    virtual void UpdateIcons() override;
    virtual void Update() override {}

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
    QPointer<RepositoryManagerComposedAddButton> m_RepositoryAdd, m_BranchCreate;
    QPointer<RepositoryManagerComposedDeleteButton> m_RepositoryDelete, m_BranchDelete;
    QPointer<RepositoryManagerComposedUpdateButton> m_RepositoryUpdate, m_BranchUpdate;
    Settings *m_Settings;
    QPointer<GitRepository> m_GitRepository;
    QStringList m_Repositories;
    QString m_OldBranch;
};

#endif  // REPOSITORYMANAGERCARD_HPP