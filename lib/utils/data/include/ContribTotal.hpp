#ifndef CONTRIBTOTAL_HPP
#define CONTRIBTOTAL_HPP

class ContribTotal {
  public:
    ContribTotal(int count = 0, int year = 0) : m_Count(count), m_Year(year) {}
    /**
     * @brief GETTERS
     */
    int GetCount() const { return m_Count; }
    int GetYear() const { return m_Year; }

    /**
     * @brief SETTERS
     */
    void SetCount(int count) { m_Count = count; }
    void SetYear(int year) { m_Year = year; }

  private:
    int m_Count;
    int m_Year;
};

#endif  // CONTRIBTOTAL_HPP