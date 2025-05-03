#include "MainWindowConnections.hpp"

#include <qglobal.h>

#include <QDesktopServices>

#include "AboutDialog.hpp"
#include "GitHubFetchAdapterWithUser.hpp"
#include "Logger.hpp"
#include "RepositoryCardConnections.hpp"
#include "RepositoryManagerCard.hpp"
#include "RequirementsController.hpp"
#include "Settings.hpp"
#include "XFakeContribHelper.hpp"

MainWindowConnections::MainWindowConnections(Ui::MainWindow *ui) : m_Ui(ui), m_UpdateChecker(new GitHubUpdateChecker(this)), m_RequirementsController(new RequirementsController(this)) {
    this->_CreateConnections();
    this->_CheckForUpdates();
    this->_CheckForRequirements();
}

MainWindowConnections::~MainWindowConnections() {
}

void MainWindowConnections::_CreateConnections() {
    using namespace XFakeContribHelper;

    // check memory initialized
    if (!m_Ui->m_RepositoryManagerCard || !m_Ui->m_ContribCard || !m_Ui->m_UserManagerCard || !m_Ui->m_RepositoryCard || !m_Ui->m_ThemeSelectionCard) {
        Logger::log_static(QObject::tr("Memory not initialized").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
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

    safeConnect(
        m_UpdateChecker.get(),
        &GitHubUpdateChecker::si_UpdateAvailable,
        this,
        &MainWindowConnections::sl_UpdateAvailable,
        "GitHubUpdateChecker::si_UpdateAvailable -> MainWindowConnections::sl_UpdateAvailable");

    safeConnect(
        m_Ui->m_AboutAction.get(),
        &QAction::triggered,
        this,
        &MainWindowConnections::sl_AboutClicked,
        "QAction::triggered -> MainWindowConnections::sl_AboutClicked");

    safeConnect(
        m_RequirementsController.get(),
        &RequirementsController::si_RequirementChecked,
        this,
        &MainWindowConnections::sl_RequirementCheckCompleted,
        "RequirementsController::si_RequirementChecked -> MainWindowConnections::sl_RequirementCheckCompleted");

    for (auto action : m_Ui->m_LanguageActions) {
        safeConnect(
            action.get(),
            &QAction::triggered,
            this,
            &MainWindowConnections::sl_LanguageChanged,
            "QAction::triggered -> MainWindowConnections::sl_LanguageChanged");
    }

    QTimer::singleShot(0, [this]() {
        this->sl_FetchContribs();
    });
}

void MainWindowConnections::_CheckForUpdates() {
    this->m_UpdateChecker->Check();
}

void MainWindowConnections::_CheckForRequirements() {
    QStringList requirements;
    requirements << "git";
    m_RequirementsController->CheckRequirements(requirements);
}

void MainWindowConnections::sl_FetchContribs() {
    m_Ui->m_ContribCard->Update();  // clear the list
    try {
        GitHubFetchAdapterWithUser fetcherFromUser(*m_Ui->m_UserManagerCard);
        m_Fetcher = fetcherFromUser.adapt();
        connect(m_Fetcher.get(), &GitHubContribFetcher::si_AllRepliesFinished, this, &MainWindowConnections::sl_FetchCompleted);
        m_Fetcher->FetchUserContributions();
    } catch (const std::exception &e) {
        Logger::log_static(QObject::tr("Error fetching contributions: %1").arg(e.what()).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        auto msg = QString(QObject::tr("Error fetching contributions: %1").arg(e.what()));
        QMessageBox::critical(nullptr, QObject::tr("Fetch Error"), msg);
    } catch (...) {
        Logger::log_static(QObject::tr("Unknown error fetching contributions").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        auto msg = QString(QObject::tr("Unknown error fetching contributions"));
        QMessageBox::critical(nullptr, QObject::tr("Fetch Error"), msg);
    }
}

void MainWindowConnections::sl_FetchCompleted() {
    m_Ui->m_ContribCard->Update(m_Fetcher->GetContribs());
}

void MainWindowConnections::sl_PushCompleted(bool success) {
    if (QThread::currentThread() != qApp->thread()) {
        // if not in main thread, invoke the method in main thread
        QMetaObject::invokeMethod(this, "sl_PushCompleted", Qt::QueuedConnection, Q_ARG(bool, success));
        return;
    }

    if (!success) return;

    auto msg = QString(QObject::tr("All pushes completed. Do you want to reload the contributions?"));
    QMessageBox msgBox(QMessageBox::Question, QObject::tr("Reload Contributions"), msg, QMessageBox::Yes | QMessageBox::No);
    msgBox.setWindowModality(Qt::WindowModal);
    msgBox.setDefaultButton(QMessageBox::Yes);

    static bool asked = false;

    if (asked) {
        return;
    }
    asked = true;

    if (msgBox.exec() == QMessageBox::Yes) {
        this->sl_FetchContribs();
    }
    asked = false;
}

void MainWindowConnections::sl_ThemeUpdated() {
    for (auto card : m_Ui->m_Cards) {
        card->UpdateCard();
    }
}

void MainWindowConnections::sl_RequirementCheckCompleted(QString name, bool isInstalled) {
    if (!isInstalled) {
        auto msg = QString(QObject::tr("The requirement %1 is not installed. Please install it to use the application.")).arg(name);
        QMessageBox::critical(nullptr, QObject::tr("Requirement Not Found"), msg);
        exit(1);
    } else {
        Logger::log_static(QObject::tr("Requirement %1 is installed").arg(name).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
    }
}

void MainWindowConnections::sl_SetEndDate(QDate date) {
    this->m_Ui->m_RepositoryCard->SetEndDate(date);
}

void MainWindowConnections::sl_SetStartDate(QDate date) {
    this->m_Ui->m_RepositoryCard->SetStartDate(date);
}

void MainWindowConnections::sl_UpdateAvailable(QString currentVersion, QString latestVersion, QString downloadUrl) {
    auto msg = QString(QObject::tr("A new version is available: %1. Do you want to download it?")).arg(latestVersion);
    QMessageBox msgBox(QMessageBox::Question, QObject::tr("Update Available"), msg, QMessageBox::Yes | QMessageBox::No);
    msgBox.setWindowModality(Qt::WindowModal);
    msgBox.setDefaultButton(QMessageBox::Yes);

    if (msgBox.exec() == QMessageBox::Yes) {
        QDesktopServices::openUrl(QUrl(downloadUrl));
    }
}

void MainWindowConnections::sl_AboutClicked() {
    AboutDialog *aboutDialog = new AboutDialog();
    aboutDialog->setAttribute(Qt::WA_DeleteOnClose);
    aboutDialog->setWindowModality(Qt::WindowModal);
    aboutDialog->exec();
}

void MainWindowConnections::sl_LanguageChanged() {
    // uncheck all actions
    for (auto action : m_Ui->m_LanguageActions) {
        action->blockSignals(true);
        action->setChecked(false);
        action->blockSignals(false);
    }

    auto sender = qobject_cast<QAction *>(QObject::sender());
    if (sender) {
        sender->blockSignals(true);
        auto lang = sender->text();
        sender->setChecked(true);
        sender->blockSignals(false);

        auto *settings = Settings::Instance();
        settings->SetLanguage(lang);

        auto *msgBox = new QMessageBox(QMessageBox::Information, QObject::tr("Language Changed"), QObject::tr("The application will restart to apply the new language."), QMessageBox::Ok);
        msgBox->setWindowModality(Qt::WindowModal);
        msgBox->setAttribute(Qt::WA_DeleteOnClose);
        msgBox->exec();
        QString program = qApp->arguments()[0];
        QStringList arguments = qApp->arguments().mid(1);  // remove the 1st argument - the program name
        qApp->quit();
        QProcess::startDetached(program, arguments);
    }
}
