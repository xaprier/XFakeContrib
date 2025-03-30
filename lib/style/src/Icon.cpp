#include "Icon.hpp"

#include "StyleManager.hpp"

Icon::Icon(const QString& svgPath, const QSize& size) {
    QSvgRenderer renderer(svgPath);
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    renderer.render(&painter);

    QPainterPath path;
    path.addRect(pixmap.rect());

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    QString colorHex = StyleManager::GetCurrentThemeColors()["icon"];
    painter.fillPath(path, QColor(colorHex));
    painter.end();

    addPixmap(pixmap);
}
