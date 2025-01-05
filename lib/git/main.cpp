#include <qlist.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QIODevice>
#include <QProcess>

#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"
#include "test.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // first run tests
    git::tests::RunTests();

    // QString localRepoPath = "/mnt/Shared/Projects/git/priv";
    // QString commitDate = "2024-11-14 15:30:00";
    // QString branchName = "main";
    // Faker faker;
    // GitChangeHandler handler(localRepoPath);
    // GitRepository repository(localRepoPath);
    // handler.CreateChange("deneme.txt", "deneme");
    // handler.ApplyChanges();
    // QString diff = repository.Diff({"--name-only"});
    // QString checkout = repository.Checkout({branchName});
    // repository.Add({
    //     ".",
    // });
    // repository.Commit({"-m",
    //                    QString::fromStdString(faker.GetHacker()),
    //                    "--date",
    //                    commitDate});
    // repository.Push({"origin", branchName});
    // auto log = repository.Log({"--oneline"});
    return app.exec();
}
