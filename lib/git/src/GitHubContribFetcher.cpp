#include "GitHubContribFetcher.hpp"

#include "ContribTotal.hpp"
#include "GitHubAuthChecker.hpp"
#include "GitHubContribLevels.hpp"

GitHubContribFetcher::GitHubContribFetcher(const QString& username, const QString& token, QObject* parent)
    : QObject(parent), m_Username(username), m_Token(token), m_AuthChecker(QSharedPointer<GitHubAuthChecker>::create()), m_LastTokenValidation(false) {
    m_Manager = QSharedPointer<QNetworkAccessManager>::create(this);
    connect(m_AuthChecker.get(), &GitHubAuthChecker::si_AuthCheckResult, this, &GitHubContribFetcher::sl_AuthCheckResult);
    // start processing of validation token
    m_AuthChecker->CheckAuthKey(token);
}

void GitHubContribFetcher::sl_NetworkReplyFinished(QNetworkReply* reply) {
    if (!reply) {
        qDebug() << "Failed to cast sender to QNetworkReply.";
        return;
    }

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        ProcessResponse(response);
    } else {
        qDebug() << "Error fetching data:" << reply->errorString();
    }

    if (m_ActiveReplies.contains(reply)) {
        m_ActiveReplies.removeOne(reply);
    } else {
        qDebug() << "Reply not found in the active list.";
    }

    if (m_ActiveReplies.empty()) {
        QDate oneYearAgo = QDate::currentDate().addYears(-1);
        QDate currentDate = QDate::currentDate();
        int totalContributions = 0;
        for (const auto& [date, contrib] : m_Contributions) {
            int count = contrib.GetCount();
            if (date >= oneYearAgo && date <= currentDate) {
                totalContributions += count;
            }
        }
        m_TotalContributions.emplace(0, ContribTotal(totalContributions, 0));

        emit this->si_AllRepliesFinished();
    }

    reply->deleteLater();
}

void GitHubContribFetcher::sl_AuthCheckResult(bool isValid, const QString& message) {
    if (isValid) {
        qDebug() << "Token validation successful";
    } else {
        qDebug() << "Invalid token:" << message;
    }
    this->m_LastTokenValidation = isValid;
}

QDate GitHubContribFetcher::FetchFirstContributionDate() {
    // GitHub GraphQL API URL
    QUrl url("https://api.github.com/graphql");
    QNetworkRequest request(url);

    // Authorization header
    request.setRawHeader("Authorization", "Bearer " + m_Token.toUtf8());
    request.setRawHeader("Content-Type", "application/json");

    // Create GraphQL query
    QJsonObject queryObj;
    queryObj["query"] = R"(
        query($userName: String!) {
            user(login: $userName) {
                contributionsCollection {
                    contributionYears
                }
            }
        })";
    queryObj["variables"] = QJsonObject{
        {"userName", m_Username}};

    // Convert query to JSON
    QJsonDocument jsonDoc(queryObj);
    QByteArray postData = jsonDoc.toJson();

    // Send POST request
    QNetworkReply* reply = m_Manager->post(request, postData);

    // Wait for reply to finish
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response, &parseError);

        if (parseError.error == QJsonParseError::NoError) {
            QJsonObject jsonObj = jsonDoc.object();
            QJsonArray yearsArray = jsonObj["data"].toObject()["user"].toObject()["contributionsCollection"].toObject()["contributionYears"].toArray();
            if (yearsArray.isEmpty()) {
                qDebug() << "No years found in the JSON data.";
                return QDate();  // Return an invalid date
            }

            // Initialize minimum year with a large value
            int minYear = INT_MAX;

            // Find the minimum year
            for (const QJsonValue& value : yearsArray) {
                int year = value.toInt();
                if (year < minYear) {
                    minYear = year;
                }
            }

            if (minYear == INT_MAX) {
                qDebug() << "No valid years found.";
                return QDate();  // Return an invalid date
            }

            // Create a QDate object from the minimum year
            return QDate(minYear, 1, 1);  // Default to January 1st of the minimum year
        } else {
            qDebug() << "JSON Parse Error:" << parseError.errorString();
        }
    } else {
        qDebug() << "Error fetching data:" << reply->errorString();
    }

    reply->deleteLater();
    return QDate();  // return invalid date
}

void GitHubContribFetcher::FetchUserContributions() {
    QMetaObject::invokeMethod(this, "sl_FetchUserContribs", Qt::QueuedConnection);
}

void GitHubContribFetcher::sl_FetchUserContribs() {
    // first check auth key
    if (!m_LastTokenValidation && !m_AuthChecker->IsChecking()) {
        m_AuthChecker->CheckAuthKey(m_Token);
        QEventLoop loop;
        connect(m_AuthChecker.get(), &GitHubAuthChecker::si_AuthCheckResult, &loop, [&](bool isValid, const QString& message) {
            if (!isValid) {
                throw std::runtime_error("Invalid token. Please re-check the token is valid.");
            } else
                loop.quit();
        });
        loop.exec();
    }

    // Fetch the earliest contribution date
    QDate firstContributionDate = FetchFirstContributionDate();
    if (!firstContributionDate.isValid()) {
        qDebug() << "Invalid first contribution date.";
        return;
    }

    QDate currentDate = QDate::currentDate();
    QDate startDate = firstContributionDate;

    while (startDate.year() <= currentDate.year()) {
        // Convert QDate to ISO 8601 string format
        QString fromDateStr = startDate.toString(Qt::ISODate) + "T00:00:00Z";
        QString toDateStr = startDate.addYears(1).toString(Qt::ISODate) + "T00:00:00Z";
        qDebug() << "Fetching data from:" << fromDateStr << "to" << toDateStr;

        QUrl url(QString("https://api.github.com/graphql"));
        QNetworkRequest request(url);

        // Set the authorization header
        request.setRawHeader("Authorization", "Bearer " + m_Token.toUtf8());
        request.setRawHeader("Content-Type", "application/json");

        // Prepare the GraphQL query with dynamic from date
        QJsonObject queryObj;
        queryObj["query"] = QString(R"(
            query($userName: String!, $fromDate: DateTime!) {
                user(login: $userName) {
                    contributionsCollection(from: $fromDate) {
                        contributionCalendar {
                            totalContributions
                            weeks {
                                contributionDays {
                                    contributionCount
                                    contributionLevel
                                    date
                                }
                            }
                        }
                    }
                }
            })");
        queryObj["variables"] = QJsonObject{
            {"userName", m_Username},
            {"fromDate", fromDateStr}};

        QJsonDocument jsonDoc(queryObj);
        QByteArray postData = jsonDoc.toJson();

        QNetworkReply* reply = m_Manager->post(request, postData);
        m_ActiveReplies.append(reply);

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            sl_NetworkReplyFinished(reply);
        });

        // Move to the next year
        startDate = startDate.addYears(1);
    }
}

void GitHubContribFetcher::SaveFormattedJsonToFile(const QString& filename) {
    if (!m_ActiveReplies.isEmpty()) {
        QEventLoop loop;
        connect(this, &GitHubContribFetcher::si_AllRepliesFinished, &loop, &QEventLoop::quit);
        loop.exec();
    }

    if (this->m_Contributions.empty() || this->m_TotalContributions.empty()) {
        qDebug() << "No fetched data found!";
        return;
    }

    // Prepare JSON data for output
    QJsonObject totalContributionsJson;
    for (const auto& [date, total] : this->m_TotalContributions) {
        totalContributionsJson[QString::number(date)] = total.GetCount();
    }

    QJsonArray contributionsJsonArray;
    for (const auto& [date, contrib] : this->m_Contributions) {
        QJsonObject contribJson;
        contribJson["date"] = date.toString(Qt::ISODate);
        contribJson["count"] = contrib.GetCount();
        contribJson["level"] = contrib.GetLevel();
        contributionsJsonArray.append(contribJson);
    }

    QJsonObject jsonObj;
    jsonObj["total"] = totalContributionsJson;
    jsonObj["contributions"] = contributionsJsonArray;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray formattedJson = jsonDoc.toJson(QJsonDocument::Indented);

    // Write formatted JSON to file
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(formattedJson);
        file.close();
        qDebug() << "Formatted JSON data saved to" << filename;
    } else {
        qDebug() << "Failed to open file for writing:" << filename;
    }
}

void GitHubContribFetcher::ProcessResponse(const QByteArray& response) {
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parse Error:" << parseError.errorString();
        return;
    }

    QJsonObject contribCalendarObj = jsonDoc.object()["data"].toObject()["user"].toObject()["contributionsCollection"].toObject()["contributionCalendar"].toObject();
    int totalContributions = contribCalendarObj["totalContributions"].toInt(0);
    // Parse daily contributions
    QJsonArray weeksArray = contribCalendarObj["weeks"].toArray();
    int year = QDate::fromString(weeksArray.first().toObject()["contributionDays"].toArray().first().toObject()["date"].toString(), Qt::ISODate).year();
    m_TotalContributions.emplace(year, ContribTotal(totalContributions, year));
    for (const QJsonValue& weekValue : weeksArray) {
        QJsonObject weekObj = weekValue.toObject();
        QJsonArray contributionDaysArray = weekObj["contributionDays"].toArray();
        for (const QJsonValue& dayValue : contributionDaysArray) {
            QJsonObject dayObj = dayValue.toObject();
            int count = dayObj["contributionCount"].toInt();
            // get level value from keys
            std::string levelKey = dayObj["contributionLevel"].toString().toStdString();
            int level = 0;
            auto it = GitHubContribLevels.find(levelKey);
            if (it != GitHubContribLevels.end()) {
                level = it->second;
            }

            QDate date = QDate::fromString(dayObj["date"].toString(), Qt::ISODate);
            m_Contributions[date] = Contrib(level, count, date);
        }
    }
}