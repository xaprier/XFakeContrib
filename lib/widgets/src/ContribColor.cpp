#include "ContribColor.hpp"

ContribColor::ContribColor(int contribCount, int maxContrib)
    : QColor(getColorForContrib(contribCount, maxContrib)) {}

QColor ContribColor::getColorForContrib(int contribCount, int maxContrib) {
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

ContribLevel ContribColor::calculateContribLevel(int contribCount, int maxContrib) {
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