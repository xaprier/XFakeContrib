#include "Application.hpp"
#include "Config.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[]) {
    Application app(argc, argv, PROJECT_NAME, PROJECT_VERSION, PROJECT_ORGANIZATION);
    MainWindow& window = MainWindow::Instance();
    window.show();
    return app.exec();
}
