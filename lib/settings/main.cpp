#include <QCoreApplication>

#include "Settings.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    auto& settings = Settings::Instance();
    QStringList repos;
    repos << "/mnt/Shared/Projects/git/priv" << "/mnt/Shared/Projects/git/fillupcommit";

    settings.SetRepositories(repos);
    return app.exec();
}