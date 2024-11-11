#ifndef CONTRIB_HPP
#define CONTRIB_HPP

#include <QDate>

class Contrib {
  public:
    Contrib(int level = 0, int count = 0, QDate date = QDate::currentDate()) : m_Level(level), m_Count(count), m_Date(date) {}

    /**
     * @brief GETTERS
     */
    int GetLevel() const { return m_Level; }
    int GetCount() const { return m_Count; }
    QDate GetDate() const { return m_Date; }

    /**
     * @brief SETTERS
     */
    void SetLevel(int level) { m_Level = level; }
    void SetCount(int count) { m_Count = count; }
    void SetDate(QDate date) { m_Date = date; }

  private:
    int m_Level;
    int m_Count;
    QDate m_Date;
};

#endif  // CONTRIB_HPP