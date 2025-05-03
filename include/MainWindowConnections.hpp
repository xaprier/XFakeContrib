#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <QMessageBox>
#include <QObject>

#include "GitHubContribFetcher.hpp"
#include "GitHubUpdateChecker.hpp"
#include "MainWindowUI.hpp"
#include "RequirementsController.hpp"

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
    void sl_PushCompleted(bool success);
    void sl_ThemeUpdated();
    void sl_RequirementCheckCompleted(QString name, bool isInstalled);
    void sl_SetEndDate(QDate date);
    void sl_SetStartDate(QDate date);
    void sl_UpdateAvailable(QString currentVersion, QString latestVersion, QString downloadUrl);
    void sl_AboutClicked();
    void sl_LanguageChanged();

  private:
    Ui::MainWindow *m_Ui;
    QSharedPointer<GitHubContribFetcher> m_Fetcher;
    QSharedPointer<GitHubUpdateChecker> m_UpdateChecker;
    QSharedPointer<RequirementsController> m_RequirementsController;
};

#endif  // MAINWINDOWCONNECTIONS_HPP