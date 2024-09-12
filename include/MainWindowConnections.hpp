#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <QObject>

#include "MainWindowUI.hpp"

class MainWindowConnections : public Ui::MainWindow {
    Q_OBJECT
  public:
    explicit MainWindowConnections(Ui::MainWindow *parent = nullptr);

  private:
    void CreateConnections();
};

#endif  // MAINWINDOWCONNECTIONS_HPP