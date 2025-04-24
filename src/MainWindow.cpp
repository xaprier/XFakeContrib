#include "MainWindow.hpp"

#include "MainWindowUI.hpp"

MainWindow* MainWindow::Instance() {
    static MainWindow* obj = nullptr;
    if (!obj) {
        obj = new MainWindow();
        connect(qApp, &QCoreApplication::aboutToQuit, obj, &MainWindow::deleteLater);
    }
    return obj;
}

MainWindow::MainWindow(QMainWindow* parent) : Ui::MainWindow(parent) {
    m_Connections = new MainWindowConnections(this);
}

MainWindow::~MainWindow() {
}
