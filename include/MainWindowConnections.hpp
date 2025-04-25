#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <QMessageBox>
#include <QObject>

#include "GitHubContribFetcher.hpp"
#include "GitHubUpdateChecker.hpp"
#include "MainWindowUI.hpp"

class MainWindowConnections : public QObject {
    Q_OBJECT
  public:
    explicit MainWindowConnections(Ui::MainWindow *ui = nullptr);
    ~MainWindowConnections();

  protected:
    void _CreateConnections();
    void _CheckForUpdates();
    void _CheckForRequirements();

  protected slots:
    void sl_FetchContribs();
    void sl_FetchCompleted();
    void sl_PushCompleted();
    void sl_ThemeUpdated();
    void sl_RequirementCheckCompleted(const QString &name, bool isInstalled);
    void sl_SetEndDate(const QDate &date);
    void sl_SetStartDate(const QDate &date);
    void sl_UpdateAvailable(const QString &currentVersion, const QString &latestVersion, const QString &downloadUrl);

  private:
    Ui::MainWindow *m_Ui;
    QSharedPointer<GitHubContribFetcher> m_Fetcher;
    QSharedPointer<GitHubUpdateChecker> m_UpdateChecker;
};

#endif  // MAINWINDOWCONNECTIONS_HPP