#ifndef CONTRIB_HPP
#define CONTRIB_HPP

#include <QDate>

class Contrib {
  public:
    Contrib(int level = 0, int count = 0, QDate date = QDate::currentDate()) : m_Level(level), m_Count(count), m_Date(date) {}
    int getLevel() const { return m_Level; }
    int getCount() const { return m_Count; }
    QDate getDate() const { return m_Date; }

  private:
    int m_Level;
    int m_Count;
    QDate m_Date;
};

#endif  // CONTRIB_HPP