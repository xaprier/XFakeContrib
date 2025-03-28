#include "MainWindow.hpp"

#include "MainWindowUI.hpp"

MainWindow& MainWindow::Instance() {
    static MainWindow instance;
    return instance;
}

MainWindow::MainWindow(QMainWindow* parent) : Ui::MainWindow(parent) {
    m_Connections = new MainWindowConnections(this);
}

MainWindow::~MainWindow() {
}
