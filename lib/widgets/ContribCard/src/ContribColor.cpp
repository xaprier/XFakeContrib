#include "ContribColor.hpp"

#include "StyleManager.hpp"

ContribColor::ContribColor(int level)
    : QColor(_GetColorForContrib(level)) {}

QColor ContribColor::_GetColorForContrib(int level) {
    ContribLevel contribLevel = _CalculateContribLevel(level);

    QString color = StyleManager::GetCurrentThemeColors()["color1"];

    switch (contribLevel) {
        case MAX_CONTRIB:
            return color;
        case HIGH_CONTRIB:
            return _AdjustBrightness(color, 1.2);
        case MEDIUM_CONTRIB:
            return _AdjustBrightness(color, 1.4);
        case MIN_CONTRIB:
            return _AdjustBrightness(color, 1.6);
        case NO_CONTRIB:
            return _AdjustBrightness(color, 2.0);
        default:
            return QColor("#ebedf0");  // Default to light gray
    }
}

ContribLevel ContribColor::_CalculateContribLevel(int level) {
    switch (level) {
        case 0:
            return NO_CONTRIB;
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