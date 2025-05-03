#ifndef GITCHANGEEDIT_HPP
#define GITCHANGEEDIT_HPP

#include "GitChange.hpp"

#include "Git_Global.hpp"

class GIT_EXPORT GitChangeEdit : public GitChange {
    Q_OBJECT
  public:
    explicit GitChangeEdit(QString repoPath, QString fileName, QString change = "", QObject *parent = nullptr) : GitChange(repoPath, fileName, change, parent) {}
    virtual ~GitChangeEdit() = default;

    void ApplyChange() override;
    virtual QString GetChangeType() const override {
        return "Edit";
    }
};

#endif  // GITCHANGEEDIT_HPP