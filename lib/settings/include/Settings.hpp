#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>

/**
 * @class Settings
 * @brief This class manages application settings using the Singleton design pattern.
 *
 * The Settings class provides an interface to handle application settings
 * such as API keys and usernames using QSettings. It ensures that only
 * one instance of the Config class exists throughout the application's lifetime.
 */
class Settings final : public QSettings {  // NOLINT
    Q_OBJECT
  public:
    /// Disable copy constructor.
    Settings(const Settings &) = delete;

    /// Disable assignment operator.
    Settings &operator=(const Settings &) = delete;

    /// Disable move constructor
    Settings(const Settings &&) = delete;

    /// Disable move assignment operator
    Settings &operator=(const Settings &&) = delete;

    /**
     * @brief Returns the Singleton instance of the Config class.
     * @return A pointer to the single instance of the Config class.
     */
    static Settings *Instance();

    /**
     * @brief Retrieves the stored API key.
     * @return The API key as a QString.
     */
    [[nodiscard]] QString GetAPIKey() const;

    /**
     * @brief Retrieves the stored username.
     * @return The username as a QString.
     */
    [[nodiscard]] QString GetUsername() const;

    /**
     * @brief Retrieves the stored repositories.
     * @return The list of repository paths as a QStringList.
     */
    [[nodiscard]] QStringList GetRepositories() const;

    /**
     * @brief Retrieves the maximum random commit count
     *
     * @return quint32 the maximum count
     */
    [[nodiscard]] quint32 GetRandomMax() const;

    /**
     * @brief Sets the API key and stores it in the settings.
     * @param key The API key to store.
     */
    void SetAPIKey(const QString &key);

    /**
     * @brief Sets the username and stores it in the settings.
     * @param name The username to store.
     */
    void SetUsername(const QString &name);

    /**
     * @brief Sets the repositories and stores them in the settings.
     *
     * @param repos The list of repository paths to store.
     */
    void SetRepositories(const QStringList &repos);

    /**
     * @brief Sets the maximum random commit count and stores it in the settings
     *
     * @param count The maximum count
     */
    void SetRandomMax(const quint32 &count);

  private:
    /**
     * @brief Constructor for the Config class.
     *
     * The constructor is private to enforce the Singleton pattern.
     * Initializes QSettings with the organization's and application's names.
     */
    Settings();

    /**
     * @brief Destructor for the Config class.
     *
     * Cleans up resources when the Config instance is destroyed.
     */
    ~Settings() = default;  // NOLINT

    /// A pointer to the Singleton instance of the Config class.
    static Settings *m_Instance;  // NOLINT

  private:
    QString m_Key;        ///< Stores the API key.
    QString m_Username;   ///< Stores the username.
    quint32 m_RandomMax;  ///< Stores the random maximum commit count
    QStringList m_Repos;  ///< Stores the repositories.
};

#endif  // SETTINGS_HPP
