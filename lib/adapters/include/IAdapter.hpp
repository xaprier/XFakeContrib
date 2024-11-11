#ifndef IADAPTER_HPP
#define IADAPTER_HPP

#include <QSharedPointer>

template <typename AdapteeType, typename TargetType>
class IAdapter {
  public:
    IAdapter(const AdapteeType &adaptee) : m_Adaptee(adaptee) {}
    virtual ~IAdapter() = default;

    virtual QSharedPointer<TargetType> adapt() const = 0;

  protected:
    const AdapteeType &m_Adaptee;
};

#endif  // IADAPTER_HPP
