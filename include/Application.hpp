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
    void _SetAppLanguage();
    void _SetAppIcon();

  private:
    QString m_ApplicationName;
    QString m_ApplicationVersion;
    QString m_OrganizationName;
    QString m_StyleSheet;
    Settings *m_Settings;
};

#endif  // APPLICATION_HPP