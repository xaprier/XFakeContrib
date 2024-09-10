#ifndef MAINWINDOWWIDGETS_HPP
#define MAINWINDOWWIDGETS_HPP

#include <QObject>

#include "MainWindow.hpp"

namespace Ui {
class MainWindow;
}

class MainWindowWidgetHandler : public QObject {
    Q_OBJECT
  public:
    explicit MainWindowWidgetHandler(Ui::MainWindow *ui = nullptr, QObject *parent = nullptr);

  private:
    friend class MainWindow;
    Ui::MainWindow *m_Ui;
};

#endif  // MAINWINDOWWIDGETS_HPP