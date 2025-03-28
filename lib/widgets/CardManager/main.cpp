
#include <QApplication>

#include "CardManager.hpp"
#include "UserManagerCard.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    UserManagerCard *card = new UserManagerCard();
    CardManager *cardManager = new CardManager(card->GetIcon(), card->GetName(), card);
    cardManager->show();
    return app.exec();
}