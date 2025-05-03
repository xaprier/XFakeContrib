#include "MainWindowUI.hpp"

#include "Application.hpp"

namespace Ui {
MainWindow::MainWindow(QMainWindow* parent) : QMainWindow(parent) {
    this->_SetupUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::_SetupUI() {
    this->_SetupMemory();
    this->_SetupWidgets();
    this->_SetupLayouts();

    // Set the central widget in the main window
    m_CentralWidget->setLayout(m_ParentLayout.get());
    setCentralWidget(m_CentralWidget.get());

    // add the toolbar to the main window
    addToolBar(Qt::TopToolBarArea, m_ToolBar.get());
    m_ToolBar->addAction(m_AboutAction.get());
    m_ToolBar->addSeparator();
    m_ToolBar->addAction(m_LanguageAction.get());
}

void MainWindow::_SetupMemory() {
    // Create a central widget
    m_CentralWidget = QSharedPointer<QWidget>::create(this);

    // Set up the layout for the central widget
    m_ParentLayout = QSharedPointer<QGridLayout>::create(m_CentralWidget.get());

    // Set up ThemeSelectionCard
    m_ThemeSelectionCard = QSharedPointer<ThemeSelectionCard>::create(m_CentralWidget.get());

    // Set up UserManagerCard
    m_UserManagerCard = QSharedPointer<UserManagerCard>::create(m_CentralWidget.get());

    // Set up RepositoryManagerCard
    m_RepositoryManagerCard = QSharedPointer<RepositoryManagerCard>::create(m_CentralWidget.get());

    // Set up RepositoryCard
    m_RepositoryCard = QSharedPointer<RepositoryCard>::create(m_CentralWidget.get());

    // Set up ContribCard
    m_ContribCard = QSharedPointer<ContribCard>::create(m_CentralWidget.get());

    // Set up toolbar
    m_ToolBar = QSharedPointer<QToolBar>::create(this);
    m_ToolBar->setMovable(false);
    m_ToolBar->setFloatable(false);
    m_ToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_ToolBar->setIconSize(QSize(16, 16));

    // Set up the About action
    m_AboutAction = QSharedPointer<QAction>::create(QObject::tr("About"), this);
    m_AboutAction->setIcon(QIcon::fromTheme("help-about"));
    m_AboutAction->setToolTip(QObject::tr("About"));

    // Set up the Language menu
    m_LanguageMenu = QSharedPointer<QMenu>::create(this);
    auto languages = Application::SupportedLanguages();
    for (const auto& lang : languages) {
        auto action = QSharedPointer<QAction>::create(lang, this);
        action->setCheckable(true);
        m_LanguageMenu->addAction(action.get());
        m_LanguageActions.append(action);
    }

    m_LanguageAction = QSharedPointer<QAction>::create(QObject::tr("Language "), this);
    m_LanguageAction->setToolTip(QObject::tr("Language"));
    m_LanguageAction->setMenu(m_LanguageMenu.get());
    m_LanguageAction->setIcon(QIcon::fromTheme("preferences-desktop-locale"));

    // Add the cards to the list
    m_Cards[Cards::CONTRIB_CARD] = QSharedPointer<CardManager>::create(m_ContribCard->GetIcon(), m_ContribCard->GetName(), m_ContribCard.get(), m_CentralWidget.get());
    m_Cards[Cards::REPOSITORY_CARD] = QSharedPointer<CardManager>::create(m_RepositoryCard->GetIcon(), m_RepositoryCard->GetName(), m_RepositoryCard.get(), m_CentralWidget.get());
    m_Cards[Cards::REPOSITORY_MANAGER_CARD] = QSharedPointer<CardManager>::create(m_RepositoryManagerCard->GetIcon(), m_RepositoryManagerCard->GetName(), m_RepositoryManagerCard.get(), m_CentralWidget.get());
    m_Cards[Cards::THEME_SELECTION_CARD] = QSharedPointer<CardManager>::create(m_ThemeSelectionCard->GetIcon(), m_ThemeSelectionCard->GetName(), m_ThemeSelectionCard.get(), m_CentralWidget.get());
    m_Cards[Cards::USER_MANAGER_CARD] = QSharedPointer<CardManager>::create(m_UserManagerCard->GetIcon(), m_UserManagerCard->GetName(), m_UserManagerCard.get(), m_CentralWidget.get());
}

void MainWindow::_SetupWidgets() {
    // Add a button to the layout
    m_ParentLayout->addWidget(m_Cards[Cards::USER_MANAGER_CARD].get(), 0, 1, 1, 1);
    m_ParentLayout->addWidget(m_Cards[Cards::THEME_SELECTION_CARD].get(), 0, 0, 1, 1);
    m_ParentLayout->addWidget(m_Cards[Cards::REPOSITORY_CARD].get(), 0, 2, 2, 3);
    m_ParentLayout->addWidget(m_Cards[Cards::REPOSITORY_MANAGER_CARD].get(), 1, 0, 1, 2);
    m_ParentLayout->addWidget(m_Cards[Cards::CONTRIB_CARD].get(), 2, 0, 1, 4);

    m_ParentLayout->setSpacing(3);
    m_ParentLayout->setContentsMargins(3, 3, 3, 3);
}

void MainWindow::_SetupLayouts() {
    m_Cards[Cards::USER_MANAGER_CARD]->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_Cards[Cards::REPOSITORY_MANAGER_CARD]->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    m_Cards[Cards::REPOSITORY_CARD]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_Cards[Cards::CONTRIB_CARD]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_ParentLayout->setColumnStretch(0, 0);
    m_ParentLayout->setColumnStretch(1, 1);
    m_ParentLayout->setRowStretch(0, 2);  // more space for RepositoryManagerCard
    m_ParentLayout->setRowStretch(1, 2);
    m_ParentLayout->setColumnStretch(2, 2);  // more space for RepositoryCard
    m_ParentLayout->setColumnStretch(2, 2);

    m_ParentLayout->setRowStretch(2, 5);  // more space for ContribCard

}

}  // namespace Ui