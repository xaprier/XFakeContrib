#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QApplication>
#include <QIcon>

#include "Settings.hpp"
#include "StyleManager.hpp"

class Application : public QApplication {
  public:
    Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &orgName);
    ~Application();
    void SetApplicationName(const QString &name);
    void SetApplicationVersion(const QString &version);
    void SetOrganizationName(const QString &name);
    void UpdateStyleSheet();

    static QTranslator translator;
    static StyleManager styleManager;

  private:
    void
    _SetAppLanguage();
    void _SetAppIcon();
    QString m_applicationName;
    QString m_applicationVersion;
    QString m_organizationName;
    QString m_styleSheet;
    Settings &settings;
};

#endif  // APPLICATION_HPP