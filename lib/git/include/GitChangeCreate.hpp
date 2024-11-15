#ifndef GITCHANGECREATE_HPP
#define GITCHANGECREATE_HPP

#include "GitChange.hpp"

class GitChangeCreate : public GitChange {
    Q_OBJECT
  public:
    explicit GitChangeCreate(QString repoPath, QString fileName, QString change = "", QObject *parent = nullptr) : GitChange(repoPath, fileName, change, parent) {}
    virtual ~GitChangeCreate() = default;

    void ApplyChange() override;
    virtual QString GetChangeType() const override {
        return "Create";
    }
};

#endif  // GITCHANGECREATE_HPP