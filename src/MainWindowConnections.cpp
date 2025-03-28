#include "MainWindowConnections.hpp"

#include <QtConcurrent/qtconcurrentmap.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <qnamespace.h>

#include "GitHubFetchAdapterWithUser.hpp"
#include "RepositoryCardConnections.hpp"

MainWindowConnections::MainWindowConnections(Ui::MainWindow *ui) : m_Ui(ui) {
    this->_CreateConnections();
}

void MainWindowConnections::_CreateConnections() {
    connect(m_Ui->m_RepositoryManagerCard.get(), &RepositoryManagerCard::si_RepositoriesUpdated, m_Ui->m_RepositoryCard->GetConnections(), &RepositoryCardConnections::sl_RepositoriesUpdated);
    connect(m_Ui->m_ContribCard.get(), &ContribCard::si_Reload, this, &MainWindowConnections::sl_FetchContribs);
    connect(m_Ui->m_UserManagerCard.get(), &UserManagerCard::si_UserUpdated, this, &MainWindowConnections::sl_FetchContribs);
    connect(m_Ui->m_RepositoryCard->GetConnections(), &RepositoryCardConnections::si_PushesCompleted, this, &MainWindowConnections::sl_PushCompleted, Qt::QueuedConnection);

    QTimer::singleShot(0, [this]() {
        this->sl_FetchContribs();
    });
}

void MainWindowConnections::sl_FetchContribs() {
    m_Ui->m_ContribCard->Update();  // clear the list

    GitHubFetchAdapterWithUser fetcherFromUser(*m_Ui->m_UserManagerCard.get());
    m_Fetcher = fetcherFromUser.adapt();
    connect(m_Fetcher.get(), &GitHubContribFetcher::si_AllRepliesFinished, this, &MainWindowConnections::sl_FetchCompleted);
    m_Fetcher->FetchUserContributions();
}

void MainWindowConnections::sl_FetchCompleted() {
    m_Ui->m_ContribCard->Update(m_Fetcher->GetContribs());
}

void MainWindowConnections::sl_PushCompleted() {
    if (QThread::currentThread() != qApp->thread()) {
        // Ana thread'de çalıştırılmasını sağla
        QMetaObject::invokeMethod(this, "sl_PushCompleted", Qt::QueuedConnection);
        return;
    }

    auto msg = QString(QObject::tr("All pushes completed. Do you want to reload the contributions?"));
    QMessageBox msgBox(QMessageBox::Question, QObject::tr("Reload Contributions"), msg, QMessageBox::Yes | QMessageBox::No);
    msgBox.setWindowModality(Qt::WindowModal);
    msgBox.setDefaultButton(QMessageBox::Yes);

    if (msgBox.exec() == QMessageBox::Yes) {
        this->sl_FetchContribs();
    }
}
