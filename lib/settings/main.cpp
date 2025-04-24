#include <QCoreApplication>

#include "Settings.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    auto* settings = Settings::Instance();
    QStringList repos;
    repos << "/mnt/Shared/Projects/git/priv" << "/mnt/Shared/Projects/git/fillupcommit";
    QString username = "xaprier";
    QString token = "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";

    settings->SetUsername(username);
    settings->SetAPIKey(token);
    settings->SetRepositories(repos);
    return app.exec();
}