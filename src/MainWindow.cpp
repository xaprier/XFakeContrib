#include "MainWindow.hpp"

MainWindow* MainWindow::m_Instance = nullptr;

MainWindow& MainWindow::Instance() {
    if (!m_Instance) {
        m_Instance = new MainWindow;
    }
    return *m_Instance;
}

MainWindow::MainWindow(MainWindowConnections* parent) : MainWindowConnections(parent) {
}

MainWindow::~MainWindow() {
}
