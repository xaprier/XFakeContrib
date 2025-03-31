#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include <QBoxLayout>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QString>
#include <QWidget>

#include "Icon.hpp"

class CardManager : public QWidget {
    Q_OBJECT
  public:
    explicit CardManager(QWidget *parent = nullptr);
    CardManager(const Icon &icon, const QString &name, QWidget *card, QWidget *parent = nullptr);
    ~CardManager();

    virtual void UpdateCard();

    void SetCardIcon(const Icon &icon);
    void SetCardName(const QString &name);
    void SetCard(QWidget *card);

    Icon GetCardIcon() const;
    QString GetCardName() const;
    QWidget *GetCard() const;

  protected:
    virtual void _SetupCard();

  private:
    QWidget *m_Card = nullptr;
    Icon m_CardIcon;
    QString m_CardName;

    QLabel *m_CardIconLabel = nullptr;
    QGroupBox *m_CardGroupBox = nullptr;
    QHBoxLayout *m_CardLayout = nullptr;
};

#endif  // CARDMANAGER_HPP