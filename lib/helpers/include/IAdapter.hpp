#ifndef IADAPTER_HPP
#define IADAPTER_HPP

#include <QDate>
#include <QSharedPointer>

template <typename Type>
class IAdapter {
  public:
    virtual ~IAdapter() = default;

    virtual QSharedPointer<Type> adapt() const = 0;
};

#endif  // IADAPTER_HPP
