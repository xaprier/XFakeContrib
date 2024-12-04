#ifndef GITCHANGEHANDLER_HPP
#define GITCHANGEHANDLER_HPP

#include <memory>

#include "Faker.hpp"
#include "GitChangeCreate.hpp"
#include "GitChangeDelete.hpp"
#include "GitChangeEdit.hpp"
#include "GitChangeQueue.hpp"

class GitChangeHandler {
  public:
    GitChangeHandler(const QString &repoPath = "") : m_RepositoryPath(repoPath) {}

    void SetRepositoryPath(const QString &repoPath = "") {
        m_RepositoryPath = repoPath;
    }

    QString GetRepositoryPath() const {
        return m_RepositoryPath;
    }

    void CreateChange(const QString &fileName) {
        QString content = QString::fromStdString(Faker::GetLorem());
        auto change = std::make_unique<GitChangeCreate>(m_RepositoryPath, fileName, content);
        m_ChangeQueue.AddChange(std::move(change));
    }

    void EditChange(const QString &fileName) {
        QString content = QString::fromStdString(Faker::GetLorem());
        auto change = std::make_unique<GitChangeEdit>(m_RepositoryPath, fileName, content);
        m_ChangeQueue.AddChange(std::move(change));
    }

    void DeleteChange(const QString &fileName) {
        auto change = std::make_unique<GitChangeDelete>(m_RepositoryPath, fileName);
        m_ChangeQueue.AddChange(std::move(change));
    }

    void ApplyChanges() {
        m_ChangeQueue.ApplyChanges();
    }

  private:
    QString m_RepositoryPath;
    GitChangeQueue m_ChangeQueue;
};

#endif  // GITCHANGEHANDLER_HPP