#include "MainWindowUI.hpp"

#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qsharedpointer.h>
#include <qvariant.h>

#include <QPushButton>

#include "ContribCard.hpp"

namespace Ui {
MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) {
    this->setupUI();
}

void MainWindow::setupUI() {
    this->setupMemory();
    this->setupWidgets();
    this->setupLayouts();

    // Set the central widget in the main window
    setCentralWidget(m_CentralWidget.get());
}

void MainWindow::setupMemory() {
    // Create a central widget
    m_CentralWidget = QSharedPointer<QWidget>::create(this);
    // Set up the layout for the central widget
    m_ParentLayout = QSharedPointer<QGridLayout>::create(m_CentralWidget.get());
    // Set up ContribCard
    m_ContribCard = QSharedPointer<ContribCard>::create();
}

void MainWindow::setupWidgets() {
    // Add a button to the layout
    QPushButton *btn = new QPushButton("alo", this);
    m_ParentLayout->addWidget(btn, 1, 0);
}

void MainWindow::setupLayouts() {
    // Set the layout to the central widget
    m_CentralWidget->setLayout(m_ParentLayout.get());
}

}  // namespace Ui