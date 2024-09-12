#ifndef MAINWINDOWUI_HPP
#define MAINWINDOWUI_HPP

#include <qgridlayout.h>
#include <qvariant.h>

#include <QMainWindow>
#include <QSharedPointer>

#include "ContribCard.hpp"

namespace Ui {
class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QMainWindow *parent = nullptr);

  private:
    void setupLayouts();
    void setupWidgets();
    void setupMemory();

  protected:
    void setupUI();
    // Layouts
    QSharedPointer<QWidget> m_CentralWidget;
    QSharedPointer<QGridLayout> m_ParentLayout;

    // Widgets
    QSharedPointer<ContribCard> m_ContribCard;
};
}  // namespace Ui

#endif  // MAINWINDOWUI_HPP