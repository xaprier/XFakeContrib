#include "GitCommitter.hpp"

GitCommitter::GitCommitter(QString repoPath, QString commitFile, QString commitMessage, QString commitContent, int commitCount, QDate commitDate, QThread *parent) : QThread(parent), m_RepoPath(repoPath), m_CommitFile(commitFile), m_CommitMessage(commitMessage), m_CommitContent(commitContent), m_CommitCount(commitCount), m_Date(commitDate) {
    this->m_Handler = new GitChangeHandler(repoPath);
    this->m_Repository = new GitRepository(repoPath);
    m_RandomContent = commitContent.isEmpty();
    m_RandomMessage = commitMessage.isEmpty();
    if (m_RandomContent || m_RandomMessage)
        m_Faker = new Faker();
}

void GitCommitter::run() {
    for (int i = 0; i < m_CommitCount; i++) {
        auto commitMessage = m_RandomMessage ? QString::fromStdString(m_Faker->GetHacker()) : m_CommitMessage;
        auto commitContent = m_RandomContent ? QString::fromStdString(m_Faker->GetLorem()) : m_CommitContent;

        if (m_RandomContent)
            m_Handler->EditChange(m_CommitFile, commitContent);
        else
            m_Handler->CreateChange(m_CommitFile, commitContent);

        m_Handler->ApplyChanges();
        m_Repository->Add({m_CommitFile});
        m_Repository->Commit({"-m",
                              commitMessage,
                              "--date",
                              m_Date.toString("yyyy-MM-dd hh:mm:ss")});
    }
    emit si_CommitterFinished(m_Date);
}
