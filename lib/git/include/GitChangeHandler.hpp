#ifndef GITCHANGEHANDLER_HPP
#define GITCHANGEHANDLER_HPP

#include <QObject>
#include <memory>

#include "GitChangeCreate.hpp"
#include "GitChangeDelete.hpp"
#include "GitChangeEdit.hpp"
#include "GitChangeQueue.hpp"

// todo: make tests
class GitChangeHandler : public QObject {
    Q_OBJECT
  public:
    GitChangeHandler(QString repoPath = "", QObject *parent = nullptr) : QObject(parent), m_RepositoryPath(std::move(repoPath)) {}

    void SetRepositoryPath(const QString &repoPath = "") {
        m_RepositoryPath = repoPath;
    }

    [[nodiscard]] QString GetRepositoryPath() const {
        return m_RepositoryPath;
    }

    void CreateChange(const QString &fileName, const QString &content) {
        auto change = std::make_unique<GitChangeCreate>(m_RepositoryPath, fileName, content);
        m_ChangeQueue.AddChange(std::move(change));
    }

    void EditChange(const QString &fileName, const QString &content) {
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