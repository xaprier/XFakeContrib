#include "MainWindow.hpp"

#include <memory>

#include "MainWindowConnections.hpp"
#include "MainWindowWidgetHandler.hpp"

MainWindow* MainWindow::m_Instance = nullptr;

MainWindow& MainWindow::Instance() {
    if (!m_Instance) {
        m_Instance = new MainWindow;
    }
    return *m_Instance;
}

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow(parent), m_Ui(new Ui::MainWindow) {
    m_Ui->setupUi(this);

    m_WidgetHandler = std::make_unique<MainWindowWidgetHandler>(this->m_Ui);
    m_ConnectionHandler = std::make_unique<MainWindowConnections>(this);
}

MainWindow::~MainWindow() {
}
