#ifndef REQUIREMENTSCONTROLLER_HPP
#define REQUIREMENTSCONTROLLER_HPP

#include <QObject>
#include <QProcess>

class RequirementsController : public QObject {
    Q_OBJECT

  public:
    explicit RequirementsController(QObject *parent = nullptr);
    ~RequirementsController();

    void CheckRequirement(const QString &program);        // Example: "git"
    void CheckRequirements(const QStringList &programs);  // Example: QStringList() << "git" << "openssl"

  signals:
    void si_RequirementChecked(const QString &program, bool installed);

  private:
    bool _IsProgramInstalled(const QString &program);
};

#endif  // REQUIREMENTSCONTROLLER_HPP