#include "RepositoryManagerCard.hpp"

#include <qinputdialog.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QSpacerItem>

#include "../design/ui_RepositoryManagerCardUI.h"

RepositoryManagerCard::RepositoryManagerCard(QWidget *parent) : m_Ui(new Ui::RepositoryManagerCardUI), m_Settings(Settings::Instance()) {
    m_Ui->setupUi(this);
    this->_SetupButtons();
    this->_SetupConnections();
    this->_LoadRepositories();
}

RepositoryManagerCard::~RepositoryManagerCard() {
    m_RepositoryAdd->deleteLater();
    m_RepositoryUpdate->deleteLater();
    m_RepositoryDelete->deleteLater();

    m_BranchCreate->deleteLater();
    m_BranchUpdate->deleteLater();
    m_BranchDelete->deleteLater();
}

void RepositoryManagerCard::_SetupButtons() {
    m_RepositoryAdd = new RepositoryManagerComposedButton;     // NOLINT
    m_RepositoryUpdate = new RepositoryManagerComposedButton;  // NOLINT
    m_RepositoryDelete = new RepositoryManagerComposedButton;  // NOLINT

    m_BranchCreate = new RepositoryManagerComposedButton;  // NOLINT
    m_BranchUpdate = new RepositoryManagerComposedButton;  // NOLINT
    m_BranchDelete = new RepositoryManagerComposedButton;  // NOLINT

    m_RepositoryAdd->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, QObject::tr("Add Repository"));
    m_RepositoryDelete->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, QObject::tr("Delete Selected Repository"));
    m_RepositoryUpdate->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, QObject::tr("Update Selected Repository"));

    m_BranchCreate->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, QObject::tr("Create Branch"));
    m_BranchDelete->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, QObject::tr("Delete Selected Branch"));
    m_BranchUpdate->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, QObject::tr("Update Selected Branch"));

    // Delete and update buttons will be disabled in first because of there will no be selected
    m_BranchDelete->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, true);
    m_BranchUpdate->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, true);

    m_RepositoryDelete->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, true);
    m_RepositoryUpdate->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, true);

    this->m_Ui->HL_repositoryButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    this->m_Ui->HL_repositoryButtonLayout->addWidget(m_RepositoryAdd);
    this->m_Ui->HL_repositoryButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    this->m_Ui->HL_repositoryButtonLayout->addWidget(m_RepositoryUpdate);
    this->m_Ui->HL_repositoryButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    this->m_Ui->HL_repositoryButtonLayout->addWidget(m_RepositoryDelete);
    this->m_Ui->HL_repositoryButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT

    this->m_Ui->HL_branchButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    this->m_Ui->HL_branchButtonLayout->addWidget(m_BranchCreate);
    this->m_Ui->HL_branchButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    this->m_Ui->HL_branchButtonLayout->addWidget(m_BranchUpdate);
    this->m_Ui->HL_branchButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    this->m_Ui->HL_branchButtonLayout->addWidget(m_BranchDelete);
    this->m_Ui->HL_branchButtonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));  // NOLINT
    // todo: set button icons
}

void RepositoryManagerCard::_SetupConnections() {
    connect(m_RepositoryAdd, &RepositoryManagerComposedButton::si_ButtonClicked, this, &RepositoryManagerCard::sl_RepositoryAddClicked);
    connect(m_RepositoryUpdate, &RepositoryManagerComposedButton::si_ButtonClicked, [this]() {
        auto item = this->m_Ui->repositoryListWidget->currentItem();
        this->m_Ui->repositoryListWidget->editItem(item);
    });
    connect(m_RepositoryDelete, &RepositoryManagerComposedButton::si_ButtonClicked, this, &RepositoryManagerCard::sl_RepositoryDeleteClicked);

    connect(m_BranchCreate, &RepositoryManagerComposedButton::si_ButtonClicked, this, &RepositoryManagerCard::sl_BranchCreateClicked);
    connect(m_BranchUpdate, &RepositoryManagerComposedButton::si_ButtonClicked, [this]() {
        auto item = this->m_Ui->branchListWidget->currentItem();
        this->m_Ui->branchListWidget->editItem(item);
    });
    connect(m_BranchDelete, &RepositoryManagerComposedButton::si_ButtonClicked, this, &RepositoryManagerCard::sl_BranchDeleteClicked);

    connect(this->m_Ui->repositoryListWidget, &QListWidget::currentRowChanged, this, &RepositoryManagerCard::sl_CurrentRowChangedForRepository);
    connect(this->m_Ui->repositoryListWidget, &QListWidget::itemChanged, this, &RepositoryManagerCard::sl_ItemChangedForRepository);

    connect(this->m_Ui->branchListWidget, &QListWidget::itemChanged, this, &RepositoryManagerCard::sl_ItemChangedForBranch);
    connect(this->m_Ui->branchListWidget, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        m_OldBranch = item->text();
    });
}

void RepositoryManagerCard::_LoadRepositories() {
    try {
        // clear all items first
        m_Repositories.clear();

        m_Repositories = this->m_Settings->GetRepositories();

        // if no repositories found, disable all buttons and comboBoxes with giving information to user
        _NoRepositoriesFound(m_Repositories.isEmpty());

        this->m_Ui->repositoryListWidget->blockSignals(true);
        this->m_Ui->repositoryListWidget->clear();

        // add items as editable
        for (const auto &repository : m_Repositories) {
            auto item = new QListWidgetItem(repository);  // NOLINT
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            this->m_Ui->repositoryListWidget->addItem(item);
        }

        this->m_Ui->repositoryListWidget->setCurrentRow(0);
        this->m_Ui->repositoryListWidget->blockSignals(false);

        auto path = this->m_Ui->repositoryListWidget->selectedItems().at(0)->text();  // first item
        if (m_GitRepository)
            m_GitRepository->SetRepositoryPath(path);
        else
            m_GitRepository = new GitRepository(path);  // NOLINT
        this->_LoadBranches();                          // load branches for active
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::_LoadBranches() {
    this->m_Ui->branchListWidget->clear();

    try {
        auto branches = m_GitRepository->Branch({"-a"}).split('\n');

        // we should delete first two characters if they are whitespaces because of indentation
        for (auto &branch : branches)
            if (branch.startsWith("  "))
                branch.remove(0, 2);

        // remove empty branches and branches that start with "remote"
        branches.erase(std::remove_if(branches.begin(), branches.end(), [](const QString &branch) { return branch.isEmpty() || branch.startsWith("remote"); }), branches.end());

        this->m_Ui->branchListWidget->blockSignals(true);
        this->m_Ui->branchListWidget->clear();
        // add items as editable
        for (const auto &branch : branches) {
            auto item = new QListWidgetItem(branch);  // NOLINT
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            this->m_Ui->branchListWidget->addItem(item);
        }
        this->m_Ui->branchListWidget->blockSignals(false);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::_NoRepositoriesFound(bool yes) {
    this->m_Ui->repositoryListWidget->setDisabled(yes);
    this->m_Ui->repositoryListWidget->setToolTip(yes ? QObject::tr("No Repositories Found. Please Add Repository.") : "");

    this->m_RepositoryDelete->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, yes);
    this->m_RepositoryUpdate->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, yes);
    this->m_RepositoryDelete->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, yes ? QObject::tr("No Repositories Found. Please Add Repository.") : QObject::tr("Delete selected repository from settings"));
    this->m_RepositoryUpdate->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, yes ? QObject::tr("No Repositories Found. Please Add Repository.") : QObject::tr("Update selected repository from settings"));

    this->m_BranchCreate->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, yes);
    this->m_BranchDelete->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, yes);
    this->m_BranchUpdate->SetDisabled(RepositoryManagerComposedButton::Status::BUTTON, yes);
    this->m_BranchCreate->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, yes ? QObject::tr("No Repositories Found. Please Add Repository.") : QObject::tr("Create new branch for selected repository."));
    this->m_BranchDelete->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, yes ? QObject::tr("No Repositories Found. Please Add Repository.") : QObject::tr("Delete selected branch for selected repository."));
    this->m_BranchUpdate->SetToolTip(RepositoryManagerComposedButton::Status::BUTTON, yes ? QObject::tr("No Repositories Found. Please Add Repository.") : QObject::tr("Update selected branch for selected repository."));

    this->m_Ui->branchListWidget->setDisabled(yes);
    this->m_Ui->branchListWidget->setToolTip(yes ? QObject::tr("No Repositories Found. Please Add Repository.") : "");
}

void RepositoryManagerCard::sl_RepositoryAddClicked(bool checked) {
    try {
        QFileDialog dialog(this, QObject::tr("Select Repository Path"));
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly);
        QString selectedPath = "";
        if (dialog.exec()) {
            selectedPath = dialog.selectedFiles().first();
        }

        // validate path is not empty
        if (selectedPath.isEmpty()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No path was selected."));
            return;
        }

        QDir dir(selectedPath);
        // Check if the directory exists
        if (!dir.exists()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("Directory not exists: %1").arg(selectedPath));
            return;
        }

        // validate permissions of the selected path
        if (!QFile::permissions(selectedPath).testFlag(QFileDevice::WriteUser)) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("Cannot write to the selected path: %1").arg(selectedPath));
            return;
        }

        // Check for duplicates in the repository list
        if (m_Repositories.contains(selectedPath)) {
            QMessageBox::information(this, QObject::tr("Info"), QObject::tr("The selected repository is already added."));
            return;
        }

        // check for a specific marker file or directory, e.g., `.git`
        if (!dir.exists(".git")) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No repository found in directory: %1\nPlease make sure the directory contains .git directory").arg(selectedPath));
            return;
        }

        // update repositories
        m_Repositories.append(selectedPath);
        m_Settings->SetRepositories(m_Repositories);
        this->_LoadRepositories();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::sl_RepositoryDeleteClicked(bool checked) {
    try {
        auto widget = this->m_Ui->repositoryListWidget;

        // control there is at least 1 selected item
        if (widget->selectedItems().isEmpty()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("There is no selected repository to delete"));
            return;
        }

        auto selectedItem = widget->selectedItems().at(0);
        auto path = selectedItem->text();

        // update repositories
        m_Repositories.removeOne(path);
        m_Settings->SetRepositories(m_Repositories);
        this->_LoadRepositories();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::sl_BranchCreateClicked(bool checked) {
    try {
        QInputDialog dialog(this);
        dialog.setInputMode(QInputDialog::TextInput);
        dialog.setToolTip(QObject::tr("Enter branch name"));

        QString branchName = "";
        if (dialog.exec()) {
            branchName = dialog.textValue();
        }

        if (branchName.isEmpty()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No branch name entered. Please enter valid branch name."));
            return;
        }

        auto branches = m_GitRepository->Branch({"-a"}).split('\n');

        // we should delete first two characters if they are whitespaces because of indentation
        for (auto &branch : branches)
            if (branch.startsWith("  ") || branch.startsWith("* "))
                branch.remove(0, 2);

        // remove empty branches and branches that start with "remote"
        branches.erase(std::remove_if(branches.begin(), branches.end(), [](const QString &branch) { return branch.isEmpty() || branch.startsWith("remote"); }), branches.end());

        if (branches.contains(branchName)) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("Entered branch name is exists. Please enter valid branch name."));
            return;
        }

        // create branch and load again in ui
        m_GitRepository->Branch({branchName});
        this->_LoadBranches();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::sl_BranchDeleteClicked(bool checked) {
    try {
        auto widget = this->m_Ui->branchListWidget;

        // control there is at least 1 selected item
        if (widget->selectedItems().isEmpty()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("There is no selected branch to delete"));
            return;
        }

        auto selectedItem = widget->selectedItems().at(0);
        auto branchName = selectedItem->text();

        // delete branch and load branches in ui again
        m_GitRepository->Branch({"-d", branchName});
        this->_LoadBranches();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::sl_CurrentRowChangedForRepository(int row) {
    try {
        if (row > m_Repositories.size() || row < 0) return;

        this->m_GitRepository->SetRepositoryPath(m_Repositories.at(row));

        this->_LoadBranches();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::sl_ItemChangedForRepository(QListWidgetItem *item) {
    try {
        if (!item) return;

        auto widget = this->m_Ui->repositoryListWidget;
        auto index = widget->row(item);
        auto newPath = item->text();
        if (index < 0 || index > m_Repositories.size()) return;
        auto oldPath = m_Repositories.at(index);

        widget->blockSignals(true);

        // validate path is not empty
        if (newPath.isEmpty()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No path was selected."));
            item->setText(oldPath);
            widget->blockSignals(false);
            return;
        }

        QDir dir(newPath);

        // Check if the directory exists
        if (!dir.exists()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("Directory not exists: %1").arg(newPath));
            item->setText(oldPath);
            widget->blockSignals(false);
            return;
        }

        // validate permissions of the selected path
        if (!QFile::permissions(newPath).testFlag(QFileDevice::WriteUser)) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("Cannot write to the selected path: %1").arg(newPath));
            item->setText(oldPath);
            widget->blockSignals(false);
            return;
        }

        // Check for duplicates in the repository list
        if (m_Repositories.contains(newPath)) {
            QMessageBox::information(this, QObject::tr("Info"), QObject::tr("The selected repository is already added."));
            item->setText(oldPath);
            widget->blockSignals(false);
            return;
        }

        // check for a specific marker file or directory, e.g., `.git`
        if (!dir.exists(".git")) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No repository found in directory: %1\nPlease make sure the directory contains .git directory").arg(newPath));
            item->setText(oldPath);
            widget->blockSignals(false);
            return;
        }

        widget->blockSignals(false);

        // update repositories
        m_Repositories[index] = newPath;
        this->m_Settings->SetRepositories(m_Repositories);
        this->_LoadRepositories();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}

void RepositoryManagerCard::sl_ItemChangedForBranch(QListWidgetItem *item) {
    try {
        if (!item) return;

        auto widget = this->m_Ui->branchListWidget;
        auto index = widget->row(item);
        auto oldBranch = m_OldBranch;
        auto newBranch = item->text();

        if (oldBranch == newBranch) return;

        widget->blockSignals(true);

        // validate path is not empty
        if (newBranch.isEmpty()) {
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No branch name entered."));
            item->setText(oldBranch);
            widget->blockSignals(false);
            return;
        }

        auto items = widget->findItems(newBranch, Qt::MatchExactly);
        if (items.size() > 1) {  // newBranch is in widget, so we should look for other matches
            QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("Branch name %1 is already exists. Please enter unique branch name.").arg(newBranch));
            item->setText(oldBranch);
            widget->blockSignals(false);
            return;
        }

        widget->blockSignals(false);

        m_GitRepository->Branch({"-m", oldBranch, newBranch});

        // update branches
        this->_LoadBranches();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("An error occured: %1").arg(e.what()));
    }
}
