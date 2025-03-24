#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include <QBoxLayout>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QString>
#include <QWidget>

class CardManager : public QWidget {
    Q_OBJECT
  public:
    explicit CardManager(QWidget *parent = nullptr);
    CardManager(const QIcon &icon, const QString &name, QWidget *card, QWidget *parent = nullptr);
    ~CardManager();

    void SetCardIcon(const QIcon &icon);
    void SetCardName(const QString &name);
    void SetCard(QWidget *card);

    QIcon GetCardIcon() const;
    QString GetCardName() const;
    QWidget *GetCard() const;

  protected:
    virtual void _SetupCard();
    virtual void _UpdateCard();

  private:
    QWidget *m_Card = nullptr;
    QIcon m_CardIcon;
    QString m_CardName;

    QLabel *m_CardIconLabel = nullptr;
    QGroupBox *m_CardGroupBox = nullptr;
    QHBoxLayout *m_CardLayout = nullptr;
};

#endif  // CARDMANAGER_HPP