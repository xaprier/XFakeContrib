#include <QApplication>

#include "UserManagerCard.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    UserManagerCard userManagerCard;
    userManagerCard.show();
    return app.exec();
}
