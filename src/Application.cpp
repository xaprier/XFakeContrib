#include "Application.hpp"
#include <QTranslator>

#include "Logger.hpp"
#include "Settings.hpp"

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

QStringList Application::SupportedLanguages() {
    QStringList languages;
    languages << "en_US";  // Default language english in application already

    QDir dir(":/translations/");
    QStringList qmFiles = dir.entryList(QStringList() << "*.qm", QDir::Files);
    if (qmFiles.isEmpty()) {
        Logger::log_static(QObject::tr("No translation files found").toStdString(), LoggingLevel::WARNING, __LINE__, __PRETTY_FUNCTION__);
        return languages;
    }

    for (const QString &fileName : qmFiles) {
        QRegularExpression re("translation_(\\w+)\\.qm");
        QRegularExpressionMatch match = re.match(fileName);
        if (match.hasMatch()) {
            QString lang = match.captured(1);
            if (!languages.contains(lang))
                languages << lang;
        }
    }

    return languages;
}

void Application::_SetAppLanguage() {
    auto *settings = Settings::Instance();

    QString lang = settings->GetLanguage();
    QLocale locale = QLocale::system();
    auto langs = this->SupportedLanguages();

    if (lang.isEmpty()) {
        lang = locale.name();
    }

    if (!langs.contains(lang)) {
        lang = langs[0];  // Default language
    } else {
        settings->SetLanguage(lang);
    }

    // Set default locale so QDate and similar use it
    QLocale::setDefault(QLocale(lang));

    QString string = QString(":/translations/translation_%1.qm").arg(lang);

    if (translator.load(string)) {
        Logger::log_static(QObject::tr("Loaded language %1").arg(lang).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
    }

    installTranslator(&translator);
}

void Application::_SetAppIcon() {
    setWindowIcon(QIcon(":/icons/XFakeContrib.png"));
}