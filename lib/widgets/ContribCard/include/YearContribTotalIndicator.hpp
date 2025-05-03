#ifndef YEARCONTRIBTOTALINDICATOR_HPP
#define YEARCONTRIBTOTALINDICATOR_HPP

#include <QLabel>

class YearContribTotalIndicator : public QLabel {
    Q_OBJECT
  public:
    YearContribTotalIndicator(int total = 0, QWidget *parent = nullptr) : m_Total(total), QLabel(parent) {
        this->SetText(total);
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    void SetText(int total = 0) {
        this->m_Total = total;
        QLabel::setText(QObject::tr("Total %1 contributions").arg(total));
    }

  private:
    int m_Total;
};

#endif  //  YEARCONTRIBTOTALINDICATOR_HPP
