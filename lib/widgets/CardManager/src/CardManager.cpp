#include "CardManager.hpp"

#include "Card.hpp"
#include "Icon.hpp"

CardManager::CardManager(QWidget *parent) : QWidget(parent), m_CardIcon(Icon("")), m_CardName(""), m_Card(nullptr) {
    this->_SetupCard();
}

CardManager::CardManager(const Icon &icon, const QString &name, QWidget *card, QWidget *parent) : QWidget(parent), m_Card(card), m_CardIcon(icon), m_CardName(name) {
    this->_SetupCard();
}

CardManager::~CardManager() {
}

void CardManager::SetCardIcon(const Icon &icon) {
    this->m_CardIcon = icon;

    this->UpdateCard();
}

void CardManager::SetCardName(const QString &name) {
    this->m_CardName = name;

    this->UpdateCard();
}

void CardManager::SetCard(QWidget *card) {
    this->m_Card = card;

    this->UpdateCard();
}

Icon CardManager::GetCardIcon() const {
    return m_CardIcon;
}

QString CardManager::GetCardName() const {
    return m_CardName;
}

QWidget *CardManager::GetCard() const {
    return m_Card;
}

void CardManager::_SetupCard() {
    m_CardGroupBox = new QGroupBox(this);
    m_CardLayout = new QHBoxLayout(m_CardGroupBox);
    m_CardIconLabel = new QLabel(m_CardGroupBox);

    m_CardLayout->addWidget(m_CardIconLabel);
    m_CardLayout->addWidget(m_Card);

    m_CardGroupBox->setLayout(m_CardLayout);

    m_CardGroupBox->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_CardGroupBox);

    this->setLayout(layout);

    this->UpdateCard();
}

void CardManager::UpdateCard() {
    m_CardGroupBox->setTitle(m_CardName);

    m_CardIcon.Update();

    QPixmap pixmap = m_CardIcon.pixmap(32, 32);
    m_CardIconLabel->setPixmap(pixmap);
    m_CardIconLabel->setFixedSize(pixmap.size());

    auto card = qobject_cast<Card *>(m_Card);
    if (card) {
        card->Update();
        card->UpdateIcons();
    }
}