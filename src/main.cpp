#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto& mainwindow = MainWindow::Instance();
    mainwindow.show();
    return app.exec();
}