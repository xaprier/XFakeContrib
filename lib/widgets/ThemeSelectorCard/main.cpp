#include <QApplication>

#include "ThemeSelectionCard.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ThemeSelectionCard w;
    w.show();

    return app.exec();
}
