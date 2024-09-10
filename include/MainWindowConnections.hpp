#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <QObject>
class MainWindow;
class MainWindowConnections : public QObject {
    Q_OBJECT
  public:
    explicit MainWindowConnections(MainWindow *mainWindow, QObject *parent = nullptr);

  private:
    void CreateConnections();

  private:
    MainWindow *m_MainWindow;
};

#endif  // MAINWINDOWCONNECTIONS_HPP