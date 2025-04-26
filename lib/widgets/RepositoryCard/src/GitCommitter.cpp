#include "GitCommitter.hpp"

QMutex GitCommitter::m_GitCommandMutex;  // NOLINT

GitCommitter::GitCommitter(QString repoPath, QString commitFile, QString commitMessage, QString commitContent,
                           quint32 commitCount, QDate commitDate, QThread *parent)
    : QThread(parent), m_RepoPath(std::move(repoPath)), m_CommitFile(std::move(commitFile)), m_RandomContent(commitContent.isEmpty()), m_RandomMessage(commitMessage.isEmpty()), m_CommitMessage(std::move(commitMessage)), m_CommitContent(std::move(commitContent)), m_CommitCount(std::move(commitCount)), m_Date(std::move(commitDate)) {
    this->m_Handler = new GitChangeHandler(m_RepoPath, this);  // NOLINT
    this->m_Repository = new GitRepository(m_RepoPath, this);  // NOLINT
    if (m_RandomContent || m_RandomMessage)
        m_Faker = std::make_unique<Faker>();  // NOLINT
}

void GitCommitter::run() {
    QString oldContent = "";
    qDebug() << "Starting commit process with" << m_CommitCount << "commits to" << m_CommitFile;
    for (int i = 0; i < m_CommitCount; i++) {
        Faker faker;
        auto commitMessage = m_RandomMessage ? QString::fromStdString(faker.GetHacker()) : m_CommitMessage;
        auto commitContent = m_RandomContent ? QString::fromStdString(faker.GetLorem()) : m_CommitContent;

        while (commitContent == oldContent && !m_RandomContent) {
            commitContent = QString::fromStdString(faker.GetLorem());
        }

        qDebug() << "Commit #" << i << "with message:" << commitContent << "and content:" << oldContent;

        oldContent = commitContent;

        if (m_RandomContent)
            m_Handler->EditChange(m_CommitFile, commitContent);
        else
            m_Handler->CreateChange(m_CommitFile, commitContent);

        QMutexLocker locker(&m_GitCommandMutex);
        m_Handler->ApplyChanges();
        QString output;
        bool success;
        success = m_Repository->Add(output, {m_CommitFile});

        if (!success) {
            emit si_CommitterError(output);
            return;
        }

        success = m_Repository->Commit(output, {"-m",
                                                commitMessage,
                                                "--date",
                                                m_Date.toString("yyyy-MM-dd hh:mm:ss")});

        if (!success) {
            emit si_CommitterError(output);
            return;
        }
    }
    emit si_CommitterFinished(m_Date);
}
