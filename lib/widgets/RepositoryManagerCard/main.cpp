#include <QApplication>

#include "RepositoryManagerCard.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RepositoryManagerCard card;
    card.show();
    return app.exec();
}
