#include "RepositoryCardConnections.hpp"

#include <qfuturewatcher.h>
#include <qglobal.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <unistd.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QtConcurrent>
#include <cmath>

#include "../design/ui_RepositoryCardUI.h"
#include "RepositoryCardCreateCommits.hpp"
#include "RepositoryCardPush.hpp"
#include "RepositoryTableItem.hpp"
#include "RepositoryTableItemConnections.hpp"
#include "XQCircularLoadingIndicator.hpp"

RepositoryCardConnections::RepositoryCardConnections(QList<RepositoryTableItem *> items, Ui::RepositoryCardUI *ui, QPointer<RepositoryTableView> tableView, QObject *base) : QObject(base), m_Ui(ui), m_Settings(Settings::Instance()), m_Items(std::move(items)), m_TableView(tableView) {
    this->_SetupConnections();
    this->_SetupDates();
    this->_UpdateButtonsStatus();  // updating widgets according to item count
}

RepositoryCardConnections::~RepositoryCardConnections() {
    for (auto watcher : m_PushWatchers) {
        watcher->future().cancel();
        watcher->future().waitForFinished();
        watcher->deleteLater();
    }
}

void RepositoryCardConnections::sl_RepositoriesUpdated() {
    m_TableView->_ReloadRepositories();
    m_Items = m_TableView->GetItems();
    for (auto item : m_Items) {
        connect(item->GetConnections(), &RepositoryTableItemConnections::si_StatusChanged, [this]() { this->_UpdateButtonsStatus(); });
        connect(item->GetConnections(), &RepositoryTableItemConnections::si_CommitterFinished, this, &RepositoryCardConnections::sl_CommitterFinished);
        connect(item->GetConnections(), &RepositoryTableItemConnections::si_AllCommittersFinished, this, &RepositoryCardConnections::sl_AllCommittersFinished);
        connect(item->GetConnections(), &RepositoryTableItemConnections::si_FileSelected, [this]() { this->_UpdateButtonsStatus(); });
        connect(item->GetConnections(), &RepositoryTableItemConnections::si_PushStarted, [this]() {
            auto pushing = std::count_if(m_Items.begin(), m_Items.end(), [](RepositoryTableItem *item) { return item->GetConnections()->IsPushing(); });
            auto indicator = qobject_cast<xaprier::Qt::Widgets::XQCircularLoadingIndicator *>(m_Ui->pushPB->Item(RepositoryCardPush::Status::LOADING));
            this->m_Ui->pushPB->SetLoading();
            if (indicator) {
                indicator->setToolTip(QObject::tr("Remained pushes: %1").arg(pushing));
            }
        });

        connect(item->GetConnections(), &RepositoryTableItemConnections::si_PushFinished, [this]() {
            // check how many items are pushing rn
            auto pushing = std::count_if(m_Items.begin(), m_Items.end(), [](RepositoryTableItem *item) {
                return item->GetConnections()->IsPushing();
            });

            if (pushing == 0) {
                QMetaObject::invokeMethod(this, [this]() {
                    emit this->si_PushesCompleted();
                    this->m_Ui->pushPB->SetButton(); }, Qt::QueuedConnection);
            }
        });
    }
}

void RepositoryCardConnections::_SetupConnections() {
    auto pushButton = qobject_cast<QPushButton *>(m_Ui->pushPB->Item(RepositoryCardPush::Status::BUTTON));
    if (!pushButton) {
        qWarning() << "Failed to cast from RepositoryCardPush to QPushButton.";
    } else {
        connect(pushButton, &QPushButton::clicked, this, &RepositoryCardConnections::sl_PushButtonClicked);
    }

    auto createCommitsButton = qobject_cast<QPushButton *>(m_Ui->createCommitsPB->Item(RepositoryCardCreateCommits::Status::BUTTON));
    if (!createCommitsButton) {
        qWarning() << "Failed to cast from RepositoryCardCreateCommits to QPushButton.";
    } else {
        connect(createCommitsButton, &QPushButton::clicked, this, &RepositoryCardConnections::sl_CreateCommitsButtonClicked);
    }

    connect(m_Ui->commitCountCB, &QCheckBox::checkStateChanged, this, &RepositoryCardConnections::sl_CommitCountCBStateChanged);
    connect(m_Ui->dateCB, &QCheckBox::checkStateChanged, this, &RepositoryCardConnections::sl_DateCBStateChanged);
    connect(m_Ui->commitMessageCB, &QCheckBox::checkStateChanged, this, &RepositoryCardConnections::sl_CommitMessageCBStateChanged);
    connect(m_Ui->commitContentCB, &QCheckBox::checkStateChanged, this, &RepositoryCardConnections::sl_CommitContentCBStateChanged);
    connect(m_Ui->commitMessageLE, &QLineEdit::textChanged, [this]() { this->_UpdateButtonsStatus(); });
    connect(m_Ui->commitContentLE, &QLineEdit::textChanged, [this]() { this->_UpdateButtonsStatus(); });
    connect(m_Ui->commitContentCB, &QCheckBox::checkStateChanged, [this]() { this->_UpdateButtonsStatus(); });
    connect(m_Ui->commitMessageCB, &QCheckBox::checkStateChanged, [this]() { this->_UpdateButtonsStatus(); });

    this->sl_RepositoriesUpdated();
}

void RepositoryCardConnections::_SetupDates() {
    QDateEdit *start = m_Ui->startDateDE;
    QDateEdit *end = m_Ui->endDateDE;

    // max date can be today
    auto currentDate = QDate::currentDate();
    end->setMaximumDate(currentDate);
    start->setMaximumDate(currentDate);
    end->setDate(currentDate);
}

void RepositoryCardConnections::_WidgetsSetEnabled(bool enabled) {
    this->m_Ui->VL_Main->setEnabled(enabled);  // we can disable main layout directly
}

void RepositoryCardConnections::sl_CreateCommitsButtonClicked(bool checked) {
    auto selectedItems = QList<RepositoryTableItem *>();
    for (auto item : m_Items) {
        if (item->IsEnabled()) {
            selectedItems << item;
        }
    }

    // guarding no item selected
    if (selectedItems.isEmpty()) {
        QMessageBox::critical(m_Ui->createCommitsPB, QObject::tr("Error"), QObject::tr("There are no selected items to create commits. Please select items first"));
        return;
    }

    // guarding file selected
    auto filesSelected = true;
    for (auto item : selectedItems) {
        // if there is no file selected on enabled items, return
        if (!item->IsFileSelected()) {
            filesSelected = false;
            break;
        }
    }

    if (!filesSelected) {
        QMessageBox::critical(m_Ui->createCommitsPB, QObject::tr("Error"), QObject::tr("There is no file selected for enabled repository. Please select files for enable repositories"));
        return;
    }

    // get date range
    auto startDate = m_Ui->dateCB->isChecked() ? QDate::currentDate() : m_Ui->startDateDE->date();
    auto endDate = m_Ui->dateCB->isChecked() ? QDate::currentDate() : m_Ui->endDateDE->date();

    // create commits
    this->_CreateCommits(startDate, endDate);
}

void RepositoryCardConnections::sl_PushButtonClicked(bool checked) {
    // turn push button to loading indicator
    for (auto item : m_Items) {
        // check if selected, otherwise continue
        if (!item->IsEnabled()) continue;

        // create future for every push operation
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        auto future = QtConcurrent::run(&RepositoryTableItem::Push, item);

#else
        auto future = QtConcurrent::run(item, &RepositoryTableItem::Push);
#endif
        // watch future to completed
        auto watcher = new QFutureWatcher<void>(this);  // NOLINT

        // Capture the index and connect the finished signal to the slot
        connect(watcher, &QFutureWatcher<void>::finished, this, [this, watcher]() {
            sl_ItemPushCompleted(watcher);
        });

        // set watcher to watch future
        watcher->setFuture(future);

        m_PushWatchers.append(watcher);
    }

    if (!m_PushWatchers.isEmpty()) {
        auto indicator = qobject_cast<xaprier::Qt::Widgets::XQCircularLoadingIndicator *>(m_Ui->pushPB->Item(RepositoryCardPush::Status::LOADING));
        this->m_Ui->pushPB->SetLoading();
        if (indicator) {
            indicator->setToolTip(QObject::tr("Remained pushes: %1").arg(m_PushWatchers.size()));
        }
    }
}

void RepositoryCardConnections::sl_CommitCountCBStateChanged(Qt::CheckState state) {
    // disable commit count if checked
    m_Ui->commitCountSP->setDisabled(state == Qt::Checked);
}

void RepositoryCardConnections::sl_DateCBStateChanged(Qt::CheckState state) {
    // disable dateedits if today is checked
    bool disable = state == Qt::Checked;
    m_Ui->startDateDE->setDisabled(disable);
    m_Ui->endDateDE->setDisabled(disable);
}

void RepositoryCardConnections::sl_CommitMessageCBStateChanged(Qt::CheckState state) {
    // disable static commit message if checked
    bool disable = state == Qt::Checked;
    m_Ui->commitMessageLE->setDisabled(disable);
}

void RepositoryCardConnections::sl_CommitContentCBStateChanged(Qt::CheckState state) {
    // disable static commit content if checked
    bool disable = state == Qt::Checked;
    m_Ui->commitContentLE->setDisabled(disable);
}

void RepositoryCardConnections::sl_StartDateChanged(const QDate &date) {
    // if start date bigger than end date, cancel
    QDateEdit *start = m_Ui->startDateDE;
    QDateEdit *end = m_Ui->endDateDE;

    start->blockSignals(true);
    if (date > end->date()) {
        QMessageBox::warning(start, QObject::tr("Date Error"), QObject::tr("Starting date cannot be bigger than end date."));
        // Cancel by resetting the start date to the end date
        start->setDate(end->date());
    }
    start->blockSignals(false);
}

void RepositoryCardConnections::sl_EndDateChanged(const QDate &date) {
    // if end date lesser than start date, cancel
    QDateEdit *start = m_Ui->startDateDE;
    QDateEdit *end = m_Ui->endDateDE;

    end->blockSignals(true);
    if (date < start->date()) {
        QMessageBox::warning(start, QObject::tr("Date Error"), QObject::tr("End date cannot be lesser than start date."));
        // Cancel by resetting the end date to the start date
        end->setDate(start->date());
    }
    end->blockSignals(false);
}

void RepositoryCardConnections::sl_CommitterFinished() {
    // update tooltip to "all" remained status
    int remained = 0;
    for (auto item : m_Items) {
        if (!item->IsEnabled()) continue;

        remained += item->GetCommitterCount();
    }

    m_Ui->pushPB->setToolTip(QObject::tr("Creating commits(%1)").arg(remained));

    auto indicator = qobject_cast<xaprier::Qt::Widgets::XQCircularLoadingIndicator *>(m_Ui->createCommitsPB->Item(RepositoryCardCreateCommits::Status::LOADING));

    if (!indicator) {
        qWarning() << "Failed to cast from RepositoryCardCreateCommits to XQCircularLoadingIndicator";
        return;
    }

    indicator->setToolTip(QObject::tr("Creating commits(%1)").arg(remained));
}

void RepositoryCardConnections::sl_AllCommittersFinished() {
    // enable button
    m_Ui->pushPB->setEnabled(true);
    m_Ui->pushPB->setToolTip(QObject::tr("Push all latest changes to remote"));

    m_Ui->createCommitsPB->SetButton();
    QMessageBox::information(m_Ui->createCommitsPB, QObject::tr("Success"), QObject::tr("All commits are created successfully"));

    auto indicator = qobject_cast<xaprier::Qt::Widgets::XQCircularLoadingIndicator *>(m_Ui->createCommitsPB->Item(RepositoryCardCreateCommits::Status::LOADING));

    if (!indicator) {
        qWarning() << "Failed to cast from RepositoryCardCreateCommits to XQCircularLoadingIndicator";
        return;
    }

    indicator->setToolTip("");  // clear tooltip
    this->_WidgetsSetEnabled(true);
}

void RepositoryCardConnections::sl_ItemPushCompleted(QFutureWatcher<void> *watcher) {
    m_PushWatchers.removeOne(watcher);

    auto indicator = qobject_cast<xaprier::Qt::Widgets::XQCircularLoadingIndicator *>(m_Ui->pushPB->Item(RepositoryCardPush::Status::LOADING));
    if (indicator)
        indicator->setToolTip(QObject::tr("Remained pushes: %1").arg(m_PushWatchers.size()));

    watcher->deleteLater();

    if (m_PushWatchers.isEmpty()) {
        // turn loading indicator to button
        this->m_Ui->pushPB->SetButton();
        emit this->si_PushesCompleted();
    }
}

quint32 RepositoryCardConnections::_GetCommitCount() const {
    auto random = this->m_Ui->commitCountCB->isChecked();

    if (random) {
        QRandomGenerator generator;
        return generator.bounded(quint32(1), m_Settings.GetRandomMax());  // todo: highest value should come from config
    }

    return this->m_Ui->commitCountSP->value();
}

QString RepositoryCardConnections::_GetCommitMessage() const {
    auto random = this->m_Ui->commitMessageCB->isChecked();
    return random ? "" : this->m_Ui->commitMessageLE->text();
}

QString RepositoryCardConnections::_GetCommitContent() const {
    auto random = this->m_Ui->commitContentCB->isChecked();
    return random ? "" : this->m_Ui->commitContentLE->text();
}

void RepositoryCardConnections::_CreateCommits(const QDate &startDate, const QDate &endDate) {
    // update button status
    m_Ui->createCommitsPB->SetLoading();
    m_Ui->pushPB->setDisabled(true);
    this->_WidgetsSetEnabled(false);

    // create commits between dates
    auto currentDate = startDate;
    auto index = 0;
    quint32 totalCommitCount = 0;
    while (currentDate <= endDate) {
        // get initials
        auto commitCount = this->_GetCommitCount();
        auto commitMessage = this->_GetCommitMessage();
        auto commitContent = this->_GetCommitContent();

        // use item signal to create a committer
        emit m_Items[index]->GetConnections()->si_CreateCommitter(commitCount, currentDate, commitMessage, commitContent);

        // update initials
        currentDate = currentDate.addDays(1);
        index = ++index % m_Items.size();
        totalCommitCount += commitCount;
    }
    m_Ui->pushPB->setToolTip(QObject::tr("Creating commits(%1)").arg(totalCommitCount));

    auto indicator = qobject_cast<xaprier::Qt::Widgets::XQCircularLoadingIndicator *>(m_Ui->createCommitsPB->Item(RepositoryCardCreateCommits::Status::LOADING));

    if (!indicator) {
        qWarning() << "Failed to cast from RepositoryCardCreateCommits to XQCircularLoadingIndicator";
        return;
    }

    indicator->setToolTip(QObject::tr("Creating commits(%1)").arg(totalCommitCount));
}

void RepositoryCardConnections::_UpdateButtonsStatus() {
    QList<RepositoryTableItem *> selectedRepos;
    bool atLeastOneRepoSelected = false;
    bool allFilesAreWritable = true;
    bool allFilesAreSelected = true;

    for (auto item : m_Items) {
        if (item->IsEnabled()) {
            selectedRepos << item;
            allFilesAreSelected &= item->IsFileSelected();
            allFilesAreWritable &= item->IsFileWritable();
        }
    }

    atLeastOneRepoSelected = !selectedRepos.isEmpty();

    auto createCommitsPB = qobject_cast<QPushButton *>(m_Ui->createCommitsPB->Item(RepositoryCardCreateCommits::Status::BUTTON));
    auto pushPB = qobject_cast<QPushButton *>(m_Ui->pushPB->Item(RepositoryCardPush::Status::BUTTON));

    if (!pushPB || !createCommitsPB) {
        qWarning() << "Failed to cast from RepositoryCardPush to QPushButton or RepositoryCardCreateCommits to QPushButton";
        return;
    }

    if (!atLeastOneRepoSelected) {
        pushPB->setDisabled(true);
        pushPB->setToolTip(QObject::tr("There must be at least one repository selected."));
        createCommitsPB->setDisabled(true);
        createCommitsPB->setToolTip(QObject::tr("There must be at least one repository selected."));
        return;
    } else {
        pushPB->setDisabled(false);
        pushPB->setToolTip("");
        createCommitsPB->setDisabled(false);
        createCommitsPB->setToolTip("");
    }

    if (!allFilesAreSelected) {
        createCommitsPB->setDisabled(true);
        createCommitsPB->setToolTip(QObject::tr("Commit file must be selected for all selected repositories."));
        return;
    } else {
        createCommitsPB->setDisabled(false);
        createCommitsPB->setToolTip("");
    }

    if (!allFilesAreWritable) {
        createCommitsPB->setDisabled(true);
        createCommitsPB->setToolTip(QObject::tr("Selected file must be writable for all selected repositories."));
        return;
    } else {
        createCommitsPB->setDisabled(false);
        createCommitsPB->setToolTip("");
    }

    auto randomContent = m_Ui->commitContentCB->isChecked();
    auto randomMessage = m_Ui->commitMessageCB->isChecked();

    if (!randomMessage && m_Ui->commitMessageLE->text().isEmpty()) {
        createCommitsPB->setDisabled(true);
        createCommitsPB->setToolTip(QObject::tr("Commit message must be filled."));
        return;
    } else {
        createCommitsPB->setDisabled(false);
        createCommitsPB->setToolTip("");
    }

    if (!randomContent && m_Ui->commitContentLE->text().isEmpty()) {
        createCommitsPB->setDisabled(true);
        createCommitsPB->setToolTip(QObject::tr("Commit content must be filled."));
        return;
    } else {
        createCommitsPB->setDisabled(false);
        createCommitsPB->setToolTip("");
    }
}
