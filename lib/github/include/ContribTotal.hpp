#ifndef CONTRIBTOTAL_HPP
#define CONTRIBTOTAL_HPP

class ContribTotal {
  public:
    ContribTotal(int count, int year) : m_Count(count), m_Year(year) {}
    int getCount() const { return m_Count; }
    int getYear() const { return m_Year; }

  private:
    int m_Count;
    int m_Year;
};

#endif  // CONTRIBTOTAL_HPP