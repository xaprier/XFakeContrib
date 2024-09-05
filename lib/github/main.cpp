#include <QCoreApplication>
#include <QDebug>

#include "ContribTotal.hpp"
#include "GitHubContribFetcher.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // username
    QString username = "xaprier";
    QString token = "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";

    // create fetcher
    GitHubContribFetcher fetcher(username, token);

    std::vector<Contrib> contribs;
    std::vector<ContribTotal> totals;

    // fetch contributions
    fetcher.fetchUserContributions();

    fetcher.saveFormattedJsonToFile("data.json");

    return app.exec();
}

// void sendGraphQLRequest(const QString& username, const QString& token) {
//     QNetworkAccessManager* manager = new QNetworkAccessManager();
//     QObject::connect(manager, &QNetworkAccessManager::finished, [](QNetworkReply* reply) {
//         if (reply->error()) {
//             qDebug() << "Error:" << reply->errorString();
//         } else {
//             QByteArray response = reply->readAll();
//             QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//             QJsonObject jsonObj = jsonDoc.object();
//             qDebug() << "Response:" << jsonObj;
//         }
//         reply->deleteLater();
//     });

//     QUrl url("https://api.github.com/graphql");
//     QNetworkRequest request(url);

//     // Set the authorization header
//     request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
//     request.setRawHeader("Content-Type", "application/json");

//     // Prepare the GraphQL query
//     QJsonObject queryObj;
//     queryObj["query"] = R"(
//         query($userName: String!) {
//             user(login: $userName) {
//                 contributionsCollection {
//                     contributionCalendar {
//                         totalContributions
//                         weeks {
//                             contributionDays {
//                                 contributionCount
//                                 date
//                             }
//                         }
//                     }
//                 }
//             }
//         })";
//     queryObj["variables"] = QJsonObject{{"userName", username}};

//     QJsonDocument jsonDoc(queryObj);
//     QByteArray postData = jsonDoc.toJson();

//     manager->post(request, postData);
// }

// int main(int argc, char* argv[]) {
//     QCoreApplication a(argc, argv);

//     // Replace these with your actual username and token
//     QString username = "xaprier";
//     QString token = "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";

//     sendGraphQLRequest(username, token);

//     return a.exec();
// }