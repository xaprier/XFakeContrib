#ifndef GITCHANGEDELETE_HPP
#define GITCHANGEDELETE_HPP

#include "GitChange.hpp"

class GitChangeDelete : public GitChange {
    Q_OBJECT
  public:
    explicit GitChangeDelete(QString repoPath, QString fileName, QString change = "", QObject *parent = nullptr) : GitChange(repoPath, fileName, change, parent) {}
    virtual ~GitChangeDelete() = default;

    void ApplyChange() override;
    virtual QString GetChangeType() const override {
        return "Delete";
    }
};

#endif  // GITCHANGEDELETE_HPP