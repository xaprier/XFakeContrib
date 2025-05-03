#ifndef REQUIREMENTSCONTROLLER_HPP
#define REQUIREMENTSCONTROLLER_HPP

#include <QObject>
#include <QProcess>

#include "Utils_Global.hpp"

class UTILS_EXPORT RequirementsController : public QObject {
    Q_OBJECT

  public:
    explicit RequirementsController(QObject *parent = nullptr);
    ~RequirementsController();

    void CheckRequirement(const QString &program);        // Example: "git"
    void CheckRequirements(const QStringList &programs);  // Example: QStringList() << "git" << "openssl"

  signals:
    void si_RequirementChecked(QString program, bool installed);

  private:
    bool _IsProgramInstalled(const QString &program);
};

#endif  // REQUIREMENTSCONTROLLER_HPP