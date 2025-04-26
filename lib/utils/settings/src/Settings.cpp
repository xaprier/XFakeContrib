#include "Settings.hpp"

#include <QCoreApplication>

#include "Config.hpp"

Settings *Settings::Instance() {
    static Settings *obj = nullptr;
    if (!obj) {
        obj = new Settings();
        connect(qApp, &QCoreApplication::aboutToQuit, obj, &Settings::deleteLater);
    }
    return obj;
}

Settings::Settings()
    : QSettings(PROJECT_ORGANIZATION, PROJECT_NAME) {
    m_Key = value("API_KEY", "").toString();
    m_Username = value("USERNAME", "").toString();
    m_Repos = value("REPOSITORIES", QStringList()).toStringList();
    m_RandomMax = value("MAX_RAND_COUNT", m_DefaultRandomMax).toUInt();
    m_Theme = value("THEME", m_DefaultTheme).toString();
    m_Language = value("LANGUAGE", "en").toString();
}

QString Settings::GetTheme() const {
    return m_Theme;
}

void Settings::SetTheme(const QString &theme) {
    m_Theme = theme;
    setValue("THEME", m_Theme);
}

QString Settings::GetAPIKey() const {
    return m_Key;
}

QString Settings::GetUsername() const {
    return m_Username;
}

QStringList Settings::GetRepositories() const {
    return m_Repos;
}

quint32 Settings::GetRandomMax() const {
    return m_RandomMax;
}

QString Settings::GetLanguage() const {
    return m_Language;
}

void Settings::SetAPIKey(const QString &key) {
    m_Key = key;
    setValue("API_KEY", m_Key);
}

void Settings::SetUsername(const QString &name) {
    m_Username = name;
    setValue("USERNAME", m_Username);
}

void Settings::SetRepositories(const QStringList &repos) {
    m_Repos = repos;
    setValue("REPOSITORIES", m_Repos);
}

void Settings::SetRandomMax(const quint32 &count) {
    m_RandomMax = count;
    setValue("MAX_RAND_COUNT", count);
}

void Settings::SetLanguage(const QString &lang) {
    m_Language = lang;
    setValue("LANGUAGE", m_Language);
}