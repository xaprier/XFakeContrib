#ifndef GITMANAGER_HPP
#define GITMANAGER_HPP

#include <QString>
#include <QStringList>

class GitManager {
  public:
    virtual ~GitManager() = default;

    /**
     * Pure virtual function to execute a specific Git operation.
     * @param arguments Arguments for the Git command.
     * @return The output of the Git command as a QString.
     */
    virtual void Execute(const QStringList &arguments, QString &output, QString &error) = 0;

    /**
     * Returns the Git command type as a QString for display.
     * @return The Git command type.
     */
    virtual QString GetCommandType() const = 0;
};

#endif  // GITMANAGER_HPP
