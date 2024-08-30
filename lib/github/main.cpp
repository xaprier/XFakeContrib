#include <qcoreapplication.h>

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

// JSON verisini satır satır formatlamak ve dosyaya kaydetme fonksiyonu
void saveFormattedJsonToFile(const QByteArray& jsonData, const QString& filename) {
    // JSON verisini parse et
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parse Error:" << parseError.errorString();
        return;
    }

    // JSON verisini satır satır (pretty print) formatla
    QByteArray formattedJson = jsonDoc.toJson(QJsonDocument::Indented);

    // Formatlanmış JSON'u dosyaya yaz
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(formattedJson);
        file.close();
        qDebug() << "Formatted JSON data saved to" << filename;
    } else {
        qDebug() << "Failed to open file for writing:" << filename;
    }
}

void fetchUserContributions(const QString& username) {
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrl url(QString("https://github-contributions-api.jogruber.de/v4/%1?y=all").arg(username));

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    // İstek tamamlandığında yanıtı işle
    QObject::connect(reply, &QNetworkReply::finished, [reply, username]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            // JSON verisini formatlayıp dosyaya kaydet
            saveFormattedJsonToFile(response, username + "_contributions.json");
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QString username = "xaprier";  // Buraya GitHub kullanıcı adınızı girin
    fetchUserContributions(username);

    return app.exec();
}
