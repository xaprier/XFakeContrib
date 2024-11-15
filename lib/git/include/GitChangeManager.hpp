#ifndef GITCHANGEMANAGER_HPP
#define GITCHANGEMANAGER_HPP

#include <queue>

#include "GitChange.hpp"

class GitChangeManager {
  public:
    GitChangeManager() = default;
    ~GitChangeManager() = default;

    void ApplyChanges() {
        while (!changes.empty()) {
            changes.front()->ApplyChange();
            changes.pop();
        }
    }

    void AddChange(std::unique_ptr<GitChange> change) {
        changes.push(std::move(change));
    }

    const std::queue<std::unique_ptr<GitChange>>& GetCurrentChanges() const {
        return changes;
    }

  private:
    std::queue<std::unique_ptr<GitChange>> changes;
};

#endif  // GITCHANGEMANAGER_HPP
