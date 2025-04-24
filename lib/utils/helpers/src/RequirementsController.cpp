#include "RequirementsController.hpp"

#include <QDebug>

RequirementsController::RequirementsController(QObject *parent)
    : QObject(parent) {
}

RequirementsController::~RequirementsController() {
}

void RequirementsController::CheckRequirement(const QString &program) {
    bool installed = _IsProgramInstalled(program);
    emit si_RequirementChecked(program, installed);
}

void RequirementsController::CheckRequirements(const QStringList &programs) {
    for (const auto &program : programs) {
        CheckRequirement(program);
    }
}

bool RequirementsController::_IsProgramInstalled(const QString &program) {
    QProcess process;
#ifdef Q_OS_WIN
    process.start("where", QStringList() << program);
#else
    process.start("which", QStringList() << program);
#endif
    process.waitForFinished();

    return !process.readAllStandardOutput().trimmed().isEmpty();
}