#include <QCoreApplication>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    qDebug() << "Data";
    app.exec();
}
