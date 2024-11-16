#include <qlist.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QIODevice>
#include <QProcess>
#include <cfloat>

#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QString localRepoPath = "/mnt/Shared/Projects/git/priv";
    QString commitDate = "2024-11-14 15:30:00";
    QString branchName = "main";
    GitChangeHandler handler(localRepoPath);
    GitRepository repository(localRepoPath);
    handler.CreateChange("deneme.txt");
    handler.ApplyChanges();
    QString diff = repository.Diff({"--name-only"});
    QString checkout = repository.Checkout({branchName});
    repository.Add({
        ".",
    });
    repository.Commit({"-m",
                       QString::fromStdString(Faker::GetHacker()),
                       "--date",
                       commitDate});
    repository.Push("origin", branchName);

    return app.exec();
}
