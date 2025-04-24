#include <QCoreApplication>
#include <QDebug>

#include "RequirementsController.hpp"

void RequirementChecked(const QString &program, bool installed) {
    if (installed) {
        qDebug() << program << "is installed!";
    } else {
        qDebug() << program << "is not installed!";
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    RequirementsController requirementsController;
    QObject::connect(&requirementsController, &RequirementsController::si_RequirementChecked, RequirementChecked);
    requirementsController.CheckRequirement("git");
    requirementsController.CheckRequirement("node");
    requirementsController.CheckRequirement("npm");
    requirementsController.CheckRequirement("XPwm");
    requirementsController.CheckRequirement("xpwm");
    requirementsController.CheckRequirement("code");

    return app.exec();
}