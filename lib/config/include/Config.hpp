#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QSettings>

/**
 * @class Config
 * @brief This class manages application settings using the Singleton design pattern.
 *
 * The Config class provides an interface to handle application settings
 * such as API keys and usernames using QSettings. It ensures that only
 * one instance of the Config class exists throughout the application's lifetime.
 */
class Config : public QSettings {
  public:
    /**
     * @brief Returns the Singleton instance of the Config class.
     * @return A pointer to the single instance of the Config class.
     */
    static Config *Instance();

    /**
     * @brief Retrieves the stored API key.
     * @return The API key as a QString.
     */
    QString getAPIKey() const;

    /**
     * @brief Retrieves the stored username.
     * @return The username as a QString.
     */
    QString getUsername() const;

    /**
     * @brief Sets the API key and stores it in the settings.
     * @param key The API key to store.
     */
    void setAPIKey(const QString &key);

    /**
     * @brief Sets the username and stores it in the settings.
     * @param name The username to store.
     */
    void setUsername(const QString &name);

  private:
    /**
     * @brief Constructor for the Config class.
     *
     * The constructor is private to enforce the Singleton pattern.
     * Initializes QSettings with the organization's and application's names.
     */
    Config();

    /**
     * @brief Destructor for the Config class.
     *
     * Cleans up resources when the Config instance is destroyed.
     */
    ~Config();

    /// A pointer to the Singleton instance of the Config class.
    static Config *m_Instance;

    /// Disable copy constructor.
    Config(const Config &) = delete;

    /// Disable assignment operator.
    Config &operator=(const Config &) = delete;

  private:
    QString m_Key;       ///< Stores the API key.
    QString m_Username;  ///< Stores the username.
};

#endif  // CONFIG_HPP
