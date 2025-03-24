#include "CardManager.hpp"

#include <qlabel.h>

CardManager::CardManager(QWidget *parent) : QWidget(parent) {
    this->_SetupCard();
}

CardManager::CardManager(const QIcon &icon, const QString &name, QWidget *card, QWidget *parent) : QWidget(parent), m_Card(card), m_CardIcon(icon), m_CardName(name) {
    this->_SetupCard();
}

CardManager::~CardManager() {
}

void CardManager::SetCardIcon(const QIcon &icon) {
    this->m_CardIcon = icon;

    this->_UpdateCard();
}

void CardManager::SetCardName(const QString &name) {
    this->m_CardName = name;

    this->_UpdateCard();
}

void CardManager::SetCard(QWidget *card) {
    this->m_Card = card;

    this->_UpdateCard();
}

QIcon CardManager::GetCardIcon() const {
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

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_CardGroupBox);

    this->setLayout(layout);

    this->_UpdateCard();
}

void CardManager::_UpdateCard() {
    m_CardGroupBox->setTitle(m_CardName);

    QPixmap pixmap = m_CardIcon.pixmap(32, 32);
    m_CardIconLabel->setPixmap(pixmap);
    m_CardIconLabel->setFixedSize(pixmap.size());
}