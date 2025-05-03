#include "RequirementsController.hpp"
#include "Logger.hpp"
#include <QStandardPaths>

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
    QString found = QStandardPaths::findExecutable(program);
    Logger::log_static(QObject::tr("Requirement %1 found at %2").arg(program).arg(found).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
    return !found.isEmpty();
}