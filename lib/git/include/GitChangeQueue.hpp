#ifndef GITCHANGEQUEUE_HPP
#define GITCHANGEQUEUE_HPP

#include <queue>

#include "GitChange.hpp"

class GitChangeQueue {
  public:
    GitChangeQueue() = default;
    ~GitChangeQueue() = default;

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

#endif  // GITCHANGEQUEUE_HPP
