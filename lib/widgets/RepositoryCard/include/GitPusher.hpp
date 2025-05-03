#ifndef GITPUSHER_HPP
#define GITPUSHER_HPP

#include <QPointer>
#include <QThread>

#include "GitRepository.hpp"

class GitPusher final : public QThread {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(GitPusher)
  public:
    GitPusher(QString repositoryPath, QThread *parent = nullptr) : QThread(parent), m_Repository(new GitRepository(repositoryPath)), m_RepoPath(std::move(repositoryPath)) {}
    ~GitPusher() final = default;

    QString GetRepositoryPath() const { return m_RepoPath; }

  signals:
    void si_ErrorOccurred(QString errorMessage);
    void si_PusherFinished();

  protected:
    void run() override;

  private:
    QPointer<GitRepository> m_Repository;
    QString m_RepoPath;
};

#endif  // GITPUSHER_HPP