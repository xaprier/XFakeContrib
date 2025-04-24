#include "Application.hpp"

#include <QTranslator>

#include "Logger.hpp"

QTranslator Application::translator = QTranslator();

Application::Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &appOrg)
    : QApplication(argc, argv), m_Settings(Settings::Instance()) {
    this->SetApplicationName(appName);
    this->SetApplicationVersion(appVersion);
    this->SetOrganizationName(appOrg);
    this->UpdateStyleSheet();
    this->_SetAppIcon();
    this->_SetAppLanguage();
}

Application::~Application() {
}

void Application::SetApplicationName(const QString &name) {
    m_ApplicationName = name;
    QApplication::setApplicationName(name);
}

void Application::SetApplicationVersion(const QString &version) {
    m_ApplicationVersion = version;
    QApplication::setApplicationVersion(version);
}

void Application::SetOrganizationName(const QString &name) {
    m_OrganizationName = name;
    QCoreApplication::setOrganizationName(name);
}

void Application::UpdateStyleSheet() {
    QString theme = m_Settings->GetTheme();
    styleManager.SetTheme(theme, *this);
}

void Application::_SetAppLanguage() {
    /** Localization */
    QLocale locale = QLocale::system();
    switch (locale.language()) {
        case QLocale::Turkish:
            if (translator.load(":/translations/translation_tr.qm")) {
                Logger::log_static(QObject::tr("Loaded language Turkish").toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
            }
            break;
        default:
            break;
    }
    installTranslator(&translator);
}

void Application::_SetAppIcon() {
    setWindowIcon(QIcon(":/icons/XFakeContrib.png"));
}