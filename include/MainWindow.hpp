#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "MainWindowConnections.hpp"

class MainWindow : public MainWindowConnections {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)
  public:
    static MainWindow &Instance();

  private:
    static MainWindow *m_Instance;
    explicit MainWindow(MainWindowConnections *parent = nullptr);
    ~MainWindow();
};

#endif  // MAINWINDOW_HPP