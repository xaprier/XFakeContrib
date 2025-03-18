#include "Application.hpp"
#include "Config.hpp"
#include "MainWindow.hpp"

QString getQSS();

int main(int argc, char *argv[]) {
    Application app(argc, argv, PROJECT_NAME, PROJECT_VERSION, PROJECT_ORGANIZATION, getQSS());
    MainWindow &window = MainWindow::Instance();
    window.show();
    return app.exec();
}

QString getQSS() {
    QFile styleFile(":/qss/style.qss");
    if (!styleFile.open(QFile::ReadOnly)) {
        Logger::log_static(QObject::tr("Style file cannot be opened").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return QString();
    }

    QString style(styleFile.readAll());
    return style;
}