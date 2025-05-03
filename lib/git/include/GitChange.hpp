#ifndef GITCHANGE_HPP
#define GITCHANGE_HPP

#include <QMutex>
#include <QObject>

#include "Git_Global.hpp"

class GIT_EXPORT GitChange : public QObject {
    Q_OBJECT
  public:
    explicit GitChange(QString repoPath, QString fileName, QString change = "", QObject *parent = nullptr) : QObject(parent), m_ReposPath(repoPath), m_FileName(fileName), m_Change(change) {}
    virtual ~GitChange() = default;

    virtual void ApplyChange() = 0;
    virtual QString GetChangeType() const = 0;

  protected:
    QString m_Change;
    QString m_ReposPath;
    QString m_FileName;

    mutable QMutex m_Mutex;  // Mutex for thread safety
};

#endif  // GITCHANGE_HPP