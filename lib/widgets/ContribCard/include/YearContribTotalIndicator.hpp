#ifndef YEARCONTRIBTOTALINDICATOR_HPP
#define YEARCONTRIBTOTALINDICATOR_HPP

#include <QLabel>

class YearContribTotalIndicator : public QLabel {
  public:
    YearContribTotalIndicator(int total = 0, QLabel *parent = nullptr) : m_Total(total), QLabel(parent) {
        this->SetText(total);
    }

    void SetText(int total = 0) {
        this->m_Total = total;
        QLabel::setText("Total " + QString::number(total) + " contributions");
    }

  private:
    int m_Total;
};

#endif  //  YEARCONTRIBTOTALINDICATOR_HPP
