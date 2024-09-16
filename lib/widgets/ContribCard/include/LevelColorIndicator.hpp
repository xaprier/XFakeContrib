#ifndef LEVELCOLORINDICATOR_HPP
#define LEVELCOLORINDICATOR_HPP

#include <qboxlayout.h>
#include <qlabel.h>
#include <qnamespace.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <cstddef>
#include <memory>

#include "DayContrib.hpp"

/**
 * @class _DayContribWithoutToolTip
 * @brief A subclass of DayContrib that disables tooltip display on hover.
 *
 * This class overrides the enterEvent to prevent showing a tooltip
 * when the cursor hovers over the widget.
 */
class _DayContribWithoutToolTip : public DayContrib {
  protected:
    /**
     * @brief Override to disable tooltip on hover.
     *
     * This function is overridden to do nothing, effectively disabling
     * the display of tooltips when the mouse enters the widget area.
     *
     * @param event The enter event object.
     */
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    void enterEvent(QEnterEvent* event) override {};
#else
    void enterEvent(QEvent* event) override {};
#endif
};

class LevelColorIndicator : public QWidget {
  public:
    /**
     * @brief Constructs the LevelColorIndicator widget.
     *
     * This constructor initializes the layout, creates the labels,
     * and adds the DayContrib widgets to the layout.
     *
     * @param parent The parent widget, if any.
     */
    LevelColorIndicator(QWidget* parent = nullptr);

  private:
    std::shared_ptr<std::array<_DayContribWithoutToolTip, 5>> m_DayContribs;
    std::shared_ptr<QLabel> m_LessLabel;
    std::shared_ptr<QLabel> m_MoreLabel;
};

#endif  // LEVELCOLORINDICATOR_HPP