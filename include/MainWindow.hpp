#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class MainWindowConnections;

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    static MainWindow &Instance();

  private:
    static MainWindow *m_Instance;
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;
    friend class MainWindowConnections;

  private:
    std::unique_ptr<MainWindowConnections> m_ConnectionHandler;
};

#endif  // MAINWINDOW_HPP