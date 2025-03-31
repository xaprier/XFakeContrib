#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <QMessageBox>
#include <QObject>

#include "GitHubContribFetcher.hpp"
#include "MainWindowUI.hpp"

class MainWindowConnections : public QObject {
    Q_OBJECT
  public:
    explicit MainWindowConnections(Ui::MainWindow *ui = nullptr);

  protected:
    void _CreateConnections();

  protected slots:
    void sl_FetchContribs();
    void sl_FetchCompleted();
    void sl_PushCompleted();
    void sl_ThemeUpdated();

  private:
    Ui::MainWindow *m_Ui;
    QSharedPointer<GitHubContribFetcher> m_Fetcher;
};

#endif  // MAINWINDOWCONNECTIONS_HPP