#include "MainWindowUI.hpp"

#include <QGridLayout>
#include <QPushButton>
#include <QSharedPointer>

#include "CardManager.hpp"
#include "ContribCard.hpp"

namespace Ui {
MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) {
    this->_SetupUI();
}

void MainWindow::_SetupUI() {
    this->_SetupMemory();
    this->_SetupWidgets();
    this->_SetupLayouts();

    // Set the central widget in the main window
    setCentralWidget(m_CentralWidget.get());
}

void MainWindow::_SetupMemory() {
    // Create a central widget
    m_CentralWidget = QSharedPointer<QWidget>::create(this);

    // Set up the layout for the central widget
    m_ParentLayout = QSharedPointer<QGridLayout>::create(m_CentralWidget.get());

    // Set up RepositoryCard
    m_RepositoryCard = QSharedPointer<RepositoryCard>::create();

    // Set up RepositoryManagerCard
    m_RepositoryManagerCard = QSharedPointer<RepositoryManagerCard>::create();

    // Set up UserManagerCard
    m_UserManagerCard = QSharedPointer<UserManagerCard>::create();

    // Set up ContribCard
    m_ContribCard = QSharedPointer<ContribCard>::create();

    // Add the cards to the list
    m_Cards[Cards::CONTRIB_CARD] = QSharedPointer<CardManager>::create(m_ContribCard->GetIcon(), m_ContribCard->GetName(), m_ContribCard.get());
    m_Cards[Cards::REPOSITORY_CARD] = QSharedPointer<CardManager>::create(m_RepositoryCard->GetIcon(), m_RepositoryCard->GetName(), m_RepositoryCard.get());
    m_Cards[Cards::REPOSITORY_MANAGER_CARD] = QSharedPointer<CardManager>::create(m_RepositoryManagerCard->GetIcon(), m_RepositoryManagerCard->GetName(), m_RepositoryManagerCard.get());
    m_Cards[Cards::USER_MANAGER_CARD] = QSharedPointer<CardManager>::create(m_UserManagerCard->GetIcon(), m_UserManagerCard->GetName(), m_UserManagerCard.get());
}

void MainWindow::_SetupWidgets() {
    // Add a button to the layout
    m_ParentLayout->addWidget(m_Cards[Cards::USER_MANAGER_CARD].get(), 0, 0, 1, 1);
    m_ParentLayout->addWidget(m_Cards[Cards::REPOSITORY_MANAGER_CARD].get(), 1, 0, 1, 1);
    m_ParentLayout->addWidget(m_Cards[Cards::REPOSITORY_CARD].get(), 0, 1, 2, 2);
    m_ParentLayout->addWidget(m_Cards[Cards::CONTRIB_CARD].get(), 2, 0, 1, 3);

    m_ParentLayout->setSpacing(3);
    m_ParentLayout->setContentsMargins(3, 3, 3, 3);
}

void MainWindow::_SetupLayouts() {
    // Set the layout to the central widget
    m_CentralWidget->setLayout(m_ParentLayout.get());

    m_Cards[Cards::USER_MANAGER_CARD]->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_Cards[Cards::REPOSITORY_MANAGER_CARD]->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    m_Cards[Cards::REPOSITORY_CARD]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_Cards[Cards::CONTRIB_CARD]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_ParentLayout->setColumnStretch(0, 1);
    m_ParentLayout->setRowStretch(0, 2);  // more space for RepositoryManagerCard
    m_ParentLayout->setRowStretch(1, 2);
    m_ParentLayout->setColumnStretch(1, 2);  // more space for RepositoryCard
    m_ParentLayout->setColumnStretch(2, 2);
}

}  // namespace Ui