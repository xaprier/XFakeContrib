#ifndef CONTRIBCOLOR_HPP
#define CONTRIBCOLOR_HPP

#include <QColor>

/**
 * @brief Enum representing different contribution levels.
 */
enum ContribLevel {
    NO_CONTRIB,     /**< No contribution */
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
     * @param contribCount Number of contributions (default is 0).
     * @param maxContrib Maximum contributions possible (default is 0).
     */
    ContribColor(int contribCount = 0, int maxContrib = 0);

  private:
    /**
     * @brief Determines the color based on the contribution count.
     *
     * @param contribCount Number of contributions.
     * @param maxContrib Maximum contributions possible.
     * @return QColor corresponding to the contribution level.
     */
    static QColor getColorForContrib(int contribCount, int maxContrib);

    /**
     * @brief Calculates the contribution level based on the contribution count and maximum contributions.
     *
     * @param contribCount Number of contributions.
     * @param maxContrib Maximum contributions possible.
     * @return ContribLevel corresponding to the contribution count.
     */
    static ContribLevel calculateContribLevel(int contribCount, int maxContrib);
};

#endif  // CONTRIBCOLOR_HPP
