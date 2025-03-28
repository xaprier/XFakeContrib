#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "MainWindowConnections.hpp"
#include "MainWindowUI.hpp"

class MainWindow : public Ui::MainWindow {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)
  public:
    static MainWindow &Instance();

  private:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

    QPointer<MainWindowConnections> m_Connections;
};

#endif  // MAINWINDOW_HPP