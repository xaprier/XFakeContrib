#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include <QObject>

class Settings;

class UserManager : public QObject {
    Q_OBJECT
  public:
    static UserManager &Instance();

    /**
     * @brief Disable move and copy constructors for Singleton
     */
    UserManager &operator=(const UserManager &) = delete;
    UserManager(const UserManager &) = delete;
    UserManager &operator=(UserManager &&) = delete;
    UserManager(UserManager &&) = delete;

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
    Settings &m_Settings;
};

#endif  // USERMANAGER_HPP