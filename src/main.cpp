#include "Application.hpp"
#include "Config.hpp"
#include "MainWindow.hpp"

#include <QMetaType>

int main(int argc, char* argv[]) {
    Application app(argc, argv, PROJECT_NAME, PROJECT_VERSION, PROJECT_ORGANIZATION);

    qRegisterMetaType<QFutureWatcher<void> *>("QFutureWatcher<void> *");

    MainWindow* window = MainWindow::Instance();
    window->setWindowTitle(PROJECT_NAME);
    window->setWindowIcon(QIcon(":/icons/XFakeContrib.png"));
    window->setMinimumSize(1280, 800);
    window->setAttribute(Qt::WA_QuitOnClose, true);
    window->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    window->show();

    return app.exec();
}
