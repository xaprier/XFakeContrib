#include <qlist.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QIODevice>
#include <QProcess>

bool pushToGitHub(const QString& localRepoPath, const QString& username, const QString& token, const QString& repoName,
                  const QString& commitDate, const QString& commitMessage, const QString& filePath) {
    // 1. Yerel repoda push izinlerini kontrol et
    QProcess process;
    process.start("git", QStringList() << "ls-remote" << "https://github.com/" + username + "/" + repoName);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    if (output.isEmpty()) {
        qDebug() << "GitHub'a erişim sağlanamadı. Lütfen kullanıcı adını ve depo adını kontrol edin.";
        return false;
    }

    // 2. Commit içeriğini ekle
    QDir::setCurrent(localRepoPath);
    // copy filePath
    process.start("git", QStringList() << "add" << filePath);
    process.waitForFinished();

    // 3. Commit'i tarih ile oluştur
    QString commitCommand = QString("git commit --date=\"%1\" -m \"%2\"").arg(commitDate, commitMessage);
    process.start(commitCommand, QStringList(), QFile::ReadWrite);
    process.waitForFinished();

    // 4. Commit'i push et
    process.start("git", QStringList() << "push" << "origin" << "main");  // 'main' yerine 'default' branch adı kullanılabilir
    process.waitForFinished();

    output = process.readAllStandardOutput();
    if (process.exitCode() != 0) {
        qDebug() << "Push işlemi başarısız oldu:" << process.readAllStandardError();
        return false;
    }

    qDebug() << "Push işlemi başarılı!" << output;
    return true;
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QString token = "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";  // github personal access token will reset later
    QString username = "xaprier";
    QString localRepoPath = "/mnt/Shared/Projects/git/priv";
    QString commitDate = "2021-11-05 15:30:00";
    QString repo = "fillupcommit";
    QString branchName = "main";
    QString filePath = "/mnt/Shared/Projects/git/qt-fakecontrib/src/main.cpp";
    QString commitMessage = "Bu test";

    if (pushToGitHub(localRepoPath, username, token, repo, commitDate, commitMessage, filePath)) {
        qDebug() << "Commit ve push işlemi başarıyla tamamlandı.";
    } else {
        qDebug() << "Bir hata oluştu.";
    }
    return app.exec();
}
