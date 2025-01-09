#include "Settings.hpp"

#include "Config.hpp"

Settings *Settings::m_Instance = nullptr;  // NOLINT

Settings *Settings::Instance() {
    if (!m_Instance) {
        m_Instance = new Settings();  // NOLINT
    }
    return m_Instance;
}

Settings::Settings()
    : QSettings(PROJECT_ORGANIZATION, PROJECT_NAME) {
    m_Key = value("API_KEY", "").toString();
    m_Username = value("USERNAME", "").toString();
    m_Repos = value("REPOSITORIES", QStringList()).toStringList();
    m_RandomMax = value("MAX_RAND_COUNT", quint32()).toUInt();
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