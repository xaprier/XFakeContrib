#ifndef GITCOMMAND_HPP
#define GITCOMMAND_HPP

#include <QString>

class GitCommand {
  public:
    enum Command {
        Status,
        Commit,
        Push,
        Pull,
        Clone,
        Checkout,
        Branch,
        Merge,
        Fetch,
        Log,
        Add,
        Reset,
        Diff,
        Remote
    };

    /**
     * Converts an enum command to the corresponding Git command string.
     * @param command The Git command enum.
     * @return The Git command as a QString.
     */
    static QString GitCommandToString(Command command) {
        switch (command) {
            case Status:
                return "status";
            case Commit:
                return "commit";
            case Push:
                return "push";
            case Pull:
                return "pull";
            case Clone:
                return "clone";
            case Checkout:
                return "checkout";
            case Branch:
                return "branch";
            case Merge:
                return "merge";
            case Fetch:
                return "fetch";
            case Log:
                return "log";
            case Add:
                return "add";
            case Reset:
                return "reset";
            case Diff:
                return "diff";
            case Remote:
                return "remote";
            default:
                return QString();
        }
    }
};

#endif  // GITCOMMAND_HPP
