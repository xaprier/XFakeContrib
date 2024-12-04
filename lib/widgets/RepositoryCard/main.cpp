#include <QApplication>

#include "RepositoryCard.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RepositoryCard card;
    card.show();
    return app.exec();
}