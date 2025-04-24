#include "Icon.hpp"

#include "StyleManager.hpp"

Icon::Icon(const QString& svgPath, const QSize& size) : m_Size(size), m_SvgPath(svgPath) {
    if (svgPath.isEmpty()) {
        return;
    }

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

void Icon::Update() {
    if (m_SvgPath.isEmpty()) {
        return;
    }
    QSvgRenderer renderer(m_SvgPath);
    QPixmap pixmap(m_Size);
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
