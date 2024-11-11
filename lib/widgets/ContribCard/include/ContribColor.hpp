#ifndef CONTRIBCOLOR_HPP
#define CONTRIBCOLOR_HPP

#include <QColor>

/**
 * @brief Enum representing different contribution levels.
 */
enum ContribLevel {
    NO_CONTRIB = 0, /**< No contribution */
    MIN_CONTRIB,    /**< Minimum contribution */
    MEDIUM_CONTRIB, /**< Medium contribution */
    HIGH_CONTRIB,   /**< High contribution */
    MAX_CONTRIB,    /**< Maximum contribution */
};

/**
 * @brief ContribColor class derived from QColor to represent colors based on contribution levels.
 */
class ContribColor : public QColor {
  public:
    /**
     * @brief Constructor for ContribColor.
     *
     * @param level level of the contribution, it decides the color.
     */
    ContribColor(int level = 0);

  private:
    /**
     * @brief Determines the color based on the contribution count.
     *
     * @param level level of the contribution, it decides the color.
     * @return QColor corresponding to the contribution level.
     */
    static QColor _GetColorForContrib(int level);

    /**
     * @brief Calculates the contribution level based on the contribution count and maximum contributions.
     *
     * @param level level of the contribution, it decides the color.
     * @return ContribLevel corresponding to the contribution count.
     */
    static ContribLevel _CalculateContribLevel(int level);
};

#endif  // CONTRIBCOLOR_HPP
