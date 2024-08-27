#ifndef CONTRIBCOLOR_HPP
#define CONTRIBCOLOR_HPP

#include <QColor>

class ContribColor : public QColor {
  public:
    // Constructor: Takes contribution count and total contributions
    ContribColor(int contribCount = 0, int maxContrib = 0)
        : QColor(getColorForContrib(contribCount, maxContrib)) {}

  private:
    // Enum for contribution levels
    enum ContribLevel {
        NO_CONTRIB,
        MIN_CONTRIB,
        MEDIUM_CONTRIB,
        HIGH_CONTRIB,
        MAX_CONTRIB,
    };

    // Function to determine the color based on contribution count
    static QColor getColorForContrib(int contribCount, int maxContrib) {
        ContribLevel level = calculateContribLevel(contribCount, maxContrib);

        switch (level) {
            case NO_CONTRIB:
                return QColor("#ebedf0");  // Light gray
            case MIN_CONTRIB:
                return QColor("#c6e48b");  // Light green
            case MEDIUM_CONTRIB:
                return QColor("#7bc96f");  // Green
            case HIGH_CONTRIB:
                return QColor("#239a3b");  // Dark green
            case MAX_CONTRIB:
                return QColor("#196127");  // Darker green
            default:
                return QColor("#ebedf0");  // Default to light gray
        }
    }

    // Function to calculate contribution level based on contribCount and maxContrib
    static ContribLevel calculateContribLevel(int contribCount, int maxContrib) {
        if (contribCount == 0) return NO_CONTRIB;

        int contribLevel = (contribCount * 4) / maxContrib;

        switch (contribLevel) {
            case 0:
            case 1:
                return MIN_CONTRIB;
            case 2:
                return MEDIUM_CONTRIB;
            case 3:
                return HIGH_CONTRIB;
            case 4:
                return MAX_CONTRIB;
            default:
                return NO_CONTRIB;
        }
    }
};

#endif  // CONTRIBCOLOR_HPP
