#ifndef GITCHANGEHANDLER_HPP
#define GITCHANGEHANDLER_HPP

#include <memory>

#include "Faker.hpp"
#include "GitChangeCreate.hpp"
#include "GitChangeDelete.hpp"
#include "GitChangeEdit.hpp"
#include "GitChangeManager.hpp"

class GitChangeHandler {
  public:
    GitChangeHandler(const QString &repoPath) : repoPath(repoPath) {}

    void CreateChange(const QString &fileName) {
        QString content = QString::fromStdString(Faker::GetLorem());
        auto change = std::make_unique<GitChangeCreate>(repoPath, fileName, content);
        changeManager.AddChange(std::move(change));
    }

    void EditChange(const QString &fileName) {
        QString content = QString::fromStdString(Faker::GetLorem());
        auto change = std::make_unique<GitChangeEdit>(repoPath, fileName, content);
        changeManager.AddChange(std::move(change));
    }

    void DeleteChange(const QString &fileName) {
        auto change = std::make_unique<GitChangeDelete>(repoPath, fileName);
        changeManager.AddChange(std::move(change));
    }

    void ApplyChanges() {
        changeManager.ApplyChanges();
    }

  private:
    QString repoPath;
    GitChangeManager changeManager;
};

#endif  // GITCHANGEHANDLER_HPP