#include "StyleManager.hpp"

#include "Logger.hpp"
#include "Settings.hpp"

void StyleManager::SetTheme(const QString &theme) {
    SetTheme(theme, *qApp);
}

void StyleManager::SetTheme(const QString &theme, QApplication &app) {
    QString themePath = QString(":/themes/%1.json").arg(theme);
    QString qssPath = QString(":/qss/style.qss");

    QMap<QString, QString> colors = LoadJSONColors(themePath);

    // invalid theme name on config, default will be used
    if (colors.isEmpty()) {
        Settings *settings = Settings::Instance();
        QString theme = settings->GetDefaultTheme();
        settings->SetTheme(theme);

        colors = LoadJSONColors(QString(":/themes/%1.json").arg(theme));
    }

    QFile qssFile(qssPath);
    if (!qssFile.open(QFile::ReadOnly | QFile::Text)) {
        Logger::log_static(QObject::tr("Cannot open qss file: %1").arg(qssPath).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    QString qssContent = QTextStream(&qssFile).readAll();
    qssFile.close();

    QString styledQSS = ProcessQSSWithColors(qssContent, colors);

    app.setStyleSheet(styledQSS);
    QApplication::processEvents();

    // save to settings
    Settings::Instance()->SetTheme(theme);
}

QStringList StyleManager::GetThemes() {
    QDir themeDir(":/themes/");
    QStringList themes;

    for (const QString &fileName : themeDir.entryList({"*.json"}, QDir::Files)) {
        themes.append(QFileInfo(fileName).baseName());
    }

    return themes;
}

QString StyleManager::GetTheme() {
    auto *settings = Settings::Instance();
    auto list = GetThemes();
    auto theme = settings->GetTheme();
    if (!list.contains(theme)) {
        theme = settings->GetDefaultTheme();
        settings->SetTheme(theme);
    }
    return theme;
}

QMap<QString, QString> StyleManager::GetCurrentThemeColors() {
    Settings *settings = Settings::Instance();
    QString theme = settings->GetTheme();
    QString themePath = QString(":/themes/%1.json").arg(theme);

    QMap<QString, QString> colors = LoadJSONColors(themePath);

    // invalid theme name on config, default will be used
    if (colors.isEmpty()) {
        Settings *settings = Settings::Instance();
        QString theme = settings->GetDefaultTheme();
        settings->SetTheme(theme);

        colors = LoadJSONColors(QString(":/themes/%1.json").arg(theme));
    }

    return colors;
}

QMap<QString, QString> StyleManager::LoadJSONColors(const QString &jsonPath) {
    QMap<QString, QString> colorMap;

    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly)) {
        Logger::log_static(QObject::tr("Cannot open JSON file: %1").arg(jsonPath).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return colorMap;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            QString key = it.key();
            QString value = it.value().toString();
            colorMap[key] = value;
        }
    } else {
        Logger::log_static(QObject::tr("Invalid JSON format in file: %1").arg(jsonPath).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
    }

    return colorMap;
}

QString StyleManager::ProcessQSSWithColors(const QString &qss, const QMap<QString, QString> &colorMap) {
    QString processedQSS = qss;

    // sort the keys by length to replace the longest keys first
    QStringList keys = colorMap.keys();
    std::sort(keys.begin(), keys.end(), [](const QString &a, const QString &b) {
        return a.length() > b.length();
    });

    for (const QString &key : keys) {
        processedQSS.replace("@" + key, colorMap.value(key));
    }

    return processedQSS;
}
