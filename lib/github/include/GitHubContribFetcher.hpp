#ifndef GITHUBCONTRIBFETCHER_HPP
#define GITHUBCONTRIBFETCHER_HPP

#include <qvariant.h>

#include <QDate>
#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include <memory>

#include "Contrib.hpp"
#include "ContribTotal.hpp"

class GitHubContribFetcher : public QObject {
    Q_OBJECT

  public:
    GitHubContribFetcher(const QString& username, QObject* parent = nullptr)
        : QObject(parent), m_Username(username) {
        manager = std::make_shared<QNetworkAccessManager>(this);
    }

    void fetchUserContributions() {
        QUrl url(QString("https://github-contributions-api.jogruber.de/v4/%1?y=all").arg(m_Username));
        QNetworkRequest request(url);
        QNetworkReply* reply = manager->get(request);

        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            processResponse(response);
        } else {
            qDebug() << "Error fetching data:" << reply->errorString();
        }

        reply->deleteLater();
    }

    void saveFormattedJsonToFile(const QString& filename) {
        if (this->m_Contributions.empty() || this->m_TotalContributions.empty()) {
            qDebug() << "No fetched data found!";
            return;
        }

        // get data from Contrib and ContribTotal objects and convert to QJson
        QJsonObject totalContributionsJson;
        for (const ContribTotal& total : this->m_TotalContributions) {
            totalContributionsJson[QString::number(total.getYear())] = total.getCount();
        }

        QJsonArray contributionsJsonArray;
        for (const Contrib& contrib : this->m_Contributions) {
            QJsonObject contribJson;
            contribJson["date"] = contrib.getDate().toString(Qt::ISODate);
            contribJson["count"] = contrib.getCount();
            contribJson["level"] = contrib.getLevel();
            contributionsJsonArray.append(contribJson);
        }

        QJsonObject jsonObj;
        jsonObj["total"] = totalContributionsJson;
        jsonObj["contributions"] = contributionsJsonArray;

        QJsonDocument jsonDoc(jsonObj);
        QByteArray formattedJson = jsonDoc.toJson(QJsonDocument::Indented);

        // write formattedJson
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(formattedJson);
            file.close();
            qDebug() << "Formatted JSON data saved to" << filename;
        } else {
            qDebug() << "Failed to open file for writing:" << filename;
        }
    }

  private:
    void processResponse(const QByteArray& response) {
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON Parse Error:" << parseError.errorString();
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        // Parse total contributions per year
        QJsonObject totalObj = jsonObj["total"].toObject();
        for (auto it = totalObj.begin(); it != totalObj.end(); ++it) {
            int year = it.key().toInt();
            int count = it.value().toInt();
            m_TotalContributions.push_back(ContribTotal(count, year));
        }

        // Parse daily contributions
        QJsonArray contributionsArray = jsonObj["contributions"].toArray();
        for (const QJsonValue& value : contributionsArray) {
            QJsonObject obj = value.toObject();
            int count = obj["count"].toInt();
            int level = obj["level"].toInt();
            QDate date = QDate::fromString(obj["date"].toString(), "yyyy-MM-dd");
            m_Contributions.push_back(Contrib(level, count, date));
        }
    }

  private:
    QString m_Username;
    std::shared_ptr<QNetworkAccessManager> manager;
    std::vector<Contrib> m_Contributions;
    std::vector<ContribTotal> m_TotalContributions;
};

#endif  // GITHUBCONTRIBFETCHER_HPP
