#ifndef IADAPTER_HPP
#define IADAPTER_HPP

#include <QDate>
#include <memory>
#include <vector>

template <typename Type>
class IAdapter {
  public:
    virtual ~IAdapter() = default;

    virtual Type* adapt() const = 0;
};

#endif  // IADAPTER_HPP
