#include "MainWindowConnections.hpp"

#include <qnamespace.h>

#include "GitHubFetchAdapterWithUser.hpp"
#include "RepositoryCardConnections.hpp"
#include "RepositoryManagerCard.hpp"
#include "RequirementsController.hpp"
#include "XFakeContribHelper.hpp"

MainWindowConnections::MainWindowConnections(Ui::MainWindow *ui) : m_Ui(ui) {
    this->_CreateConnections();
    this->_CheckForUpdates();
    this->_CheckForRequirements();
}

MainWindowConnections::~MainWindowConnections() {
}

void MainWindowConnections::_CreateConnections() {
    using namespace XFakeContribHelper;

    // check memory initialized
    if (!m_Ui->m_RepositoryManagerCard || !m_Ui->m_ContribCard || !m_Ui->m_UserManagerCard || !m_Ui->m_RepositoryCard) {
        qDebug() << "Memory not initialized";
        return;
    }

    safeConnect(
        m_Ui->m_RepositoryManagerCard.get(),
        &RepositoryManagerCard::si_RepositoriesUpdated,
        m_Ui->m_RepositoryCard->GetConnections().data(),
        &RepositoryCardConnections::sl_RepositoriesUpdated,
        "RepositoryManagerCard::si_RepositoriesUpdated -> RepositoryCardConnections::sl_RepositoriesUpdated");

    safeConnect(
        m_Ui->m_ContribCard.get(),
        &ContribCard::si_Reload,
        this,
        &MainWindowConnections::sl_FetchContribs,
        "ContribCard::si_Reload -> MainWindowConnections::sl_FetchContribs");

    safeConnect(
        m_Ui->m_UserManagerCard.get(),
        &UserManagerCard::si_UserUpdated,
        this,
        &MainWindowConnections::sl_FetchContribs,
        "UserManagerCard::si_UserUpdated -> MainWindowConnections::sl_FetchContribs");

    safeConnect(
        m_Ui->m_RepositoryCard->GetConnections().data(),
        &RepositoryCardConnections::si_PushesCompleted,
        this,
        &MainWindowConnections::sl_PushCompleted,
        "RepositoryCardConnections::si_PushesCompleted -> MainWindowConnections::sl_PushCompleted",
        Qt::QueuedConnection);

    safeConnect(
        m_Ui->m_ThemeSelectionCard.get(),
        &ThemeSelectionCard::si_ThemeUpdated,
        this,
        &MainWindowConnections::sl_ThemeUpdated,
        "ThemeSelectionCard::si_ThemeUpdated -> MainWindowConnections::sl_ThemeUpdated");

    safeConnect(
        m_Ui->m_ContribCard.get(),
        &ContribCard::si_SetEndDate,
        this,
        &MainWindowConnections::sl_SetEndDate,
        "ContribCard::si_SetEndDate -> MainWindowConnections::sl_SetEndDate");

    safeConnect(
        m_Ui->m_ContribCard.get(),
        &ContribCard::si_SetStartDate,
        this,
        &MainWindowConnections::sl_SetStartDate,
        "ContribCard::si_SetStartDate -> MainWindowConnections::sl_SetStartDate");

    QTimer::singleShot(0, [this]() {
        this->sl_FetchContribs();
    });
}

void MainWindowConnections::_CheckForUpdates() {
    // todo: implement here
}

void MainWindowConnections::_CheckForRequirements() {
    RequirementsController reqController;
    QStringList requirements;
    requirements << "git" << "openssl";
    reqController.CheckRequirements(requirements);
    connect(&reqController, &RequirementsController::si_RequirementChecked, this, &MainWindowConnections::sl_RequirementCheckCompleted);
}

void MainWindowConnections::sl_FetchContribs() {
    m_Ui->m_ContribCard->Update();  // clear the list

    GitHubFetchAdapterWithUser fetcherFromUser(*m_Ui->m_UserManagerCard);
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

void MainWindowConnections::sl_ThemeUpdated() {
    for (auto card : m_Ui->m_Cards) {
        card->UpdateCard();
    }
}

void MainWindowConnections::sl_RequirementCheckCompleted(const QString &name, bool isInstalled) {
    if (!isInstalled) {
        auto msg = QString(QObject::tr("The requirement %1 is not installed. Please install it to use the application.")).arg(name);
        QMessageBox::critical(nullptr, QObject::tr("Requirement Not Found"), msg);
        qApp->exit(1);
    } else {
        qDebug() << "Requirement" << name << "is installed.";
    }
}

void MainWindowConnections::sl_SetEndDate(const QDate &date) {
    this->m_Ui->m_RepositoryCard->SetEndDate(date);
}

void MainWindowConnections::sl_SetStartDate(const QDate &date) {
    this->m_Ui->m_RepositoryCard->SetStartDate(date);
}
