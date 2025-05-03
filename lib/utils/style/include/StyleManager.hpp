#ifndef STYLEMANAGER_HPP
#define STYLEMANAGER_HPP

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QStringList>
#include <QTextStream>

#include "Utils_Global.hpp"

class UTILS_EXPORT StyleManager {
  public:
    static void SetTheme(const QString &theme);
    static void SetTheme(const QString &theme, QApplication &app);
    static QStringList GetThemes();
    static QString GetTheme();
    static QMap<QString, QString> GetCurrentThemeColors();

  private:
    static QMap<QString, QString> LoadJSONColors(const QString &jsonPath);
    static QString ProcessQSSWithColors(const QString &qss, const QMap<QString, QString> &colorMap);
};

#endif  // STYLEMANAGER_HPP