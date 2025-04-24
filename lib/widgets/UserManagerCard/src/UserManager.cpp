#include "UserManager.hpp"

#include <qcoreapplication.h>

#include "Settings.hpp"

UserManager::UserManager(QObject* parent) : m_Settings(Settings::Instance()) {
    _LoadUsername();
    _LoadToken();
}

UserManager* UserManager::Instance() {
    static UserManager* obj = nullptr;
    if (!obj) {
        obj = new UserManager();
        connect(qApp, &QCoreApplication::aboutToQuit, obj, &UserManager::deleteLater);
    }
    return obj;
}

void UserManager::SetUsername(const QString& username) {
    m_Username = username;
}

void UserManager::SetToken(const QString& token) {
    m_Token = token;
}

QString UserManager::GetUsername() const {
    return m_Username;
}

QString UserManager::GetToken() const {
    return m_Token;
}

void UserManager::SaveCredentials() {
    _SaveUsername();
    _SaveToken();
}

void UserManager::_LoadUsername() {
    m_Username = m_Settings->GetUsername();
}

void UserManager::_LoadToken() {
    m_Token = m_Settings->GetAPIKey();
}

void UserManager::_SaveUsername() {
    m_Settings->SetUsername(m_Username);
}

void UserManager::_SaveToken() {
    m_Settings->SetAPIKey(m_Token);
}
