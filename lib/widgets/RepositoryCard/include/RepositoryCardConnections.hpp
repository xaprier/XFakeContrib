#ifndef REPOSITORYCARDCONNECTIONS_HPP
#define REPOSITORYCARDCONNECTIONS_HPP

#include <QObject>

#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"
#include "Settings.hpp"

namespace Ui {
class RepositoryCardUI;
}

class RepositoryCardConnections : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCardConnections)
  public:
    explicit RepositoryCardConnections(Settings *settings, GitChangeHandler *changeHandler, GitRepository *repository, Ui::RepositoryCardUI *ui, QObject *base = nullptr);
    ~RepositoryCardConnections() = default;

  protected:
    void sl_LogButtonClicked(bool checked);
    void sl_CreateCommitsButtonClicked(bool checked);
    void sl_PushButtonClicked(bool checked);
    void sl_SelectCommitFileClicked(bool checked);
    void sl_RepositoryIndexChanged(int index);
    void sl_BranchIndexChanged(int index);
    void sl_CommitCountCBStateChanged(int state);
    void sl_DateCBStateChanged(int state);
    void sl_CommitMessageCBStateChanged(int state);
    void sl_CommitContentCBStateChanged(int state);

  private:
    void _SetupConnections();
    void _LoadBranches();

  private:
    Ui::RepositoryCardUI *m_Ui;
    GitRepository *m_Repository;
    GitChangeHandler *m_Handler;
    Settings *m_Settings;
    QString m_CommitFile;
};

#endif  // REPOSITORYCARDCONNECTIONS_HPP