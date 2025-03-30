#ifndef ICON_HPP
#define ICON_HPP

#include <qsvgrenderer.h>

#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QSvgRenderer>

class Icon : public QIcon {
  public:
    Icon(const QString& svgPath, const QSize& size = QSize(128, 128));
};

#endif  // ICON_HPP