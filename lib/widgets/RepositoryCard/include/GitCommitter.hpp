#ifndef GITCOMMITTER_HPP
#define GITCOMMITTER_HPP

#include <QDate>
#include <QPointer>
#include <QThread>
#include <memory>

#include "Faker.hpp"
#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"

class GitCommitter final : public QThread {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(GitCommitter)
  public:
    explicit GitCommitter(QString repoPath, QString commitFile, QString commitMessage, QString commitContent, quint32 commitCount, QDate commitDate, QThread *parent = nullptr);
    ~GitCommitter() final = default;

    ///< GETTERS
    [[nodiscard]] QString RepoPath() const { return m_RepoPath; }
    [[nodiscard]] QString CommitFile() const { return m_CommitFile; }
    [[nodiscard]] QString CommitMessage() const { return m_CommitMessage; }
    [[nodiscard]] QString CommitContent() const { return m_CommitContent; }
    [[nodiscard]] quint32 CommitCount() const { return m_CommitCount; }
    [[nodiscard]] QDate CommitDate() const { return m_Date; }

    ///< SETTERS
    void SetRepoPath(QString repoPath) { m_RepoPath = repoPath; }
    void SetCommitFile(QString commitFile) { m_CommitFile = commitFile; }
    void SetCommitMessage(QString commitMessage) { m_CommitMessage = commitMessage; }
    void SetCommitContent(QString commitContent) { m_CommitContent = commitContent; }
    void SetCommitCount(quint32 commitCount) { m_CommitCount = commitCount; }
    void SetCommitDate(QDate commitDate) { m_Date = commitDate; }

  signals:
    void si_CommitterFinished(QDate date);
    void si_CommitterError(QString error);

  protected:
    void run() override;

  private:
    static QMutex m_GitCommandMutex;  // NOLINT
    bool m_RandomContent, m_RandomMessage;
    QPointer<GitChangeHandler> m_Handler;
    QPointer<GitRepository> m_Repository;
    std::unique_ptr<Faker> m_Faker;
    QString m_RepoPath, m_CommitFile, m_CommitMessage, m_CommitContent;
    quint32 m_CommitCount;
    QDate m_Date;
};

#endif  // GITCOMMITTER_HPP