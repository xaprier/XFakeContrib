#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include <QObject>

#include "Widgets_Global.hpp"

class Settings;

class WIDGETS_EXPORT UserManager : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UserManager)
  public:
    static UserManager *Instance();

    /**
     * @brief Set the token for the user
     * @param token
     */
    void SetToken(const QString &token);

    /**
     * @brief Get the token for the user
     * @return
     */
    QString GetToken() const;

    /**
     * @brief Set the username for the user
     * @param username
     */
    void SetUsername(const QString &username);

    /**
     * @brief Get the username for the user
     * @return
     */
    QString GetUsername() const;

    /**
     * @brief Save the credentials to the settings
     */
    void SaveCredentials();

  protected:
    void _LoadUsername();
    void _SaveUsername();
    void _LoadToken();
    void _SaveToken();

  private:
    explicit UserManager(QObject *parent = nullptr);
    ~UserManager() = default;

  private:
    QString m_Token, m_Username;
    Settings *m_Settings;
};

#endif  // USERMANAGER_HPP