#include "MainWindowConnections.hpp"

MainWindowConnections::MainWindowConnections(MainWindow *mainWindow, QObject *parent) : m_MainWindow(mainWindow), QObject(parent) {
    CreateConnections();
}

void MainWindowConnections::CreateConnections() {
}
