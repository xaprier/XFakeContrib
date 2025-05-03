#ifndef ICON_HPP
#define ICON_HPP

#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QSvgRenderer>

#include "Utils_Global.hpp"

class UTILS_EXPORT Icon : public QIcon {
  public:
    Icon(const QString& svgPath, const QSize& size = QSize(128, 128));
    ~Icon() = default;

    void Update();
    QString GetSvgPath() const { return m_SvgPath; }

  private:
    QSize m_Size;
    QString m_SvgPath;
};

#endif  // ICON_HPP