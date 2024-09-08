#include "Config.hpp"

Config *Config::m_Instance = nullptr;

Config *Config::Instance() {
    if (!m_Instance) {
        m_Instance = new Config();
    }
    return m_Instance;
}

QString Config::getAPIKey() const {
    return m_Key;
}

QString Config::getUsername() const {
    return m_Username;
}

void Config::setAPIKey(const QString &key) {
    m_Key = key;
    setValue("API_KEY", m_Key);
}

void Config::setUsername(const QString &name) {
    m_Username = name;
    setValue("USERNAME", m_Username);
}

Config::Config()
    : QSettings("xaprier", "FakeContrib") {
    m_Key = value("API_KEY", "").toString();
    m_Username = value("USERNAME", "").toString();
}

Config::~Config() {
}
