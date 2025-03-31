
#include <QApplication>

#include "CardManager.hpp"
#include "Icon.hpp"

class Card : public QWidget {
  public:
    Card(QWidget *parent) : QWidget(parent) {}
    virtual ~Card() {}
    virtual QString GetName() = 0;
    virtual Icon GetIcon() = 0;
};

class UserManagerCard : public Card {
  public:
    UserManagerCard(QWidget *parent) : Card(parent) {}
    ~UserManagerCard() = default;
    QString GetName() override { return "User Manager"; }
    Icon GetIcon() override { return Icon(":/icons/user_manager.svg"); }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Card *card = new UserManagerCard(nullptr);
    CardManager *cardManager = new CardManager(card->GetIcon(), card->GetName(), card);
    cardManager->show();
    return app.exec();
}