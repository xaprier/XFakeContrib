#include "RepositoryTableView.hpp"

#include <qalgorithms.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsharedpointer.h>

#include <QVBoxLayout>

#include "Logger.hpp"
#include "RepositoryTableItem.hpp"
#include "RepositoryTableItemPush.hpp"
#include "RepositoryTableItemStatus.hpp"
#include "RepositoryTableType.hpp"

RepositoryTableView::RepositoryTableView(QWidget *parent) : QWidget(parent), m_RepoTable(new QTableView(this)), m_RepoModel(new QStandardItemModel(this)), m_Settings(Settings::Instance()) {
    QVBoxLayout *layout = new QVBoxLayout(this);  // NOLINT
    layout->addWidget(m_RepoTable);
    setLayout(layout);
    this->_SetupModel();
    this->_SetupTable();
    this->_LoadRepositories();
}

RepositoryTableView::~RepositoryTableView() {
    // qDeleteAll(m_Items);
    m_Items.clear();
}

void RepositoryTableView::_ReloadRepositories() {
    this->_LoadRepositories();
}

void RepositoryTableView::_LoadRepositories() {
    m_Repositories = this->m_Settings->GetRepositories();

    Logger::log_static(QObject::tr("Repositories: %1").arg(m_Repositories.join(", ")).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);

    // if no repositories found, disable all buttons and comboBoxes with giving information to user
    if (m_Repositories.isEmpty()) {
        this->m_RepoTable->setDisabled(true);
        this->m_RepoTable->setToolTip(QObject::tr("No Repositories Found. Please Add Repository from Repository Manager"));
        // qDeleteAll(m_Items);
        m_Items.clear();
        return;
    } else {
        this->m_RepoTable->setDisabled(false);
        this->m_RepoTable->setToolTip("");
    }

    // Clear old rows before creating new ones
    this->m_RepoModel->removeRows(0, this->m_RepoModel->rowCount());

    this->m_RepoModel->setRowCount(m_Repositories.size());
    // qDeleteAll(m_Items);
    m_Items.clear();
    for (int i = 0; i < m_Repositories.size(); ++i) {
        auto absolutePath = m_Repositories.at(i);
        auto item = new RepositoryTableItem(absolutePath);  // NOLINT

        // safe qobject_cast and nullptr check
        auto setWidgetSafe = [&](int column, auto *widget) {
            if (widget) {
                m_RepoTable->setIndexWidget(m_RepoModel->index(i, column), widget);
            } else {
                Logger::log_static(QObject::tr("Failed to cast widget for column %1").arg(column).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
            }
        };

        setWidgetSafe(RepositoryTableType::REPO_STATUS, qobject_cast<RepositoryTableItemStatus *>(item->GetItem(RepositoryTableType::REPO_STATUS)));
        setWidgetSafe(RepositoryTableType::REPO_NAME, qobject_cast<RepositoryTableItemName *>(item->GetItem(RepositoryTableType::REPO_NAME)));
        setWidgetSafe(RepositoryTableType::REPO_BRANCH, qobject_cast<RepositoryTableItemBranch *>(item->GetItem(RepositoryTableType::REPO_BRANCH)));
        setWidgetSafe(RepositoryTableType::REPO_REMOTE, qobject_cast<RepositoryTableItemRemote *>(item->GetItem(RepositoryTableType::REPO_REMOTE)));
        setWidgetSafe(RepositoryTableType::REPO_COMMIT_FILE, qobject_cast<RepositoryTableItemCommitFile *>(item->GetItem(RepositoryTableType::REPO_COMMIT_FILE)));
        setWidgetSafe(RepositoryTableType::REPO_LOG, qobject_cast<RepositoryTableItemLog *>(item->GetItem(RepositoryTableType::REPO_LOG)));
        setWidgetSafe(RepositoryTableType::REPO_PUSH, qobject_cast<RepositoryTableItemPush *>(item->GetItem(RepositoryTableType::REPO_PUSH)));

        m_Items.append(item);
    }
}

void RepositoryTableView::_SetupModel() {
    // Set the number columns
    this->m_RepoModel->setColumnCount(this->m_ColumnNames.size());
    // Set the column names
    this->m_RepoModel->setHorizontalHeaderLabels(this->m_ColumnNames);
    // Set the model
    this->m_RepoTable->setModel(this->m_RepoModel);
}

void RepositoryTableView::_SetupTable() {
    // Set the column width
    this->m_RepoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->m_RepoTable->horizontalHeader()->setSectionResizeMode(RepositoryTableType::REPO_STATUS, QHeaderView::ResizeToContents);
    this->m_RepoTable->horizontalHeader()->setSectionResizeMode(RepositoryTableType::REPO_COMMIT_FILE, QHeaderView::ResizeToContents);
    this->m_RepoTable->horizontalHeader()->setSectionResizeMode(RepositoryTableType::REPO_LOG, QHeaderView::ResizeToContents);
    this->m_RepoTable->horizontalHeader()->setSectionResizeMode(RepositoryTableType::REPO_PUSH, QHeaderView::ResizeToContents);
    this->m_RepoTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}
