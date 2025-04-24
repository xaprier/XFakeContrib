#include "Application.hpp"
#include "Config.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[]) {
    Application app(argc, argv, PROJECT_NAME, PROJECT_VERSION, PROJECT_ORGANIZATION);

    MainWindow* window = MainWindow::Instance();
    window->setWindowTitle(PROJECT_NAME);
    window->setWindowIcon(QIcon(":/icons/XFakeContrib.png"));
    window->setMinimumSize(1280, 720);
    window->setAttribute(Qt::WA_QuitOnClose, true);
    window->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    window->show();

    return app.exec();
}
