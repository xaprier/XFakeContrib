#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "../design/ui_MainWindow.h"

namespace Ui {
class MainWindow;
};

class MainWindowConnections;
class MainWindowWidgetHandler;

class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)
  public:
    static MainWindow &Instance();

  private:
    static MainWindow *m_Instance;
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
    friend class MainWindowConnections;

  private:
    Ui::MainWindow *m_Ui;
    std::unique_ptr<MainWindowConnections> m_ConnectionHandler;
    std::unique_ptr<MainWindowWidgetHandler> m_WidgetHandler;
};

#endif  // MAINWINDOW_HPP