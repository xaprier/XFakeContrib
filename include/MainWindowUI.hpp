#ifndef MAINWINDOWUI_HPP
#define MAINWINDOWUI_HPP

#include <qobject.h>

#include <QAction>
#include <QGridLayout>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QSharedPointer>
#include <QToolBar>

#include "CardManager.hpp"
#include "ContribCard.hpp"
#include "RepositoryCard.hpp"
#include "RepositoryManagerCard.hpp"
#include "ThemeSelectionCard.hpp"
#include "UserManagerCard.hpp"

class MainWindow;
class MainWindowConnections;

namespace Ui {

enum class Cards {
    CONTRIB_CARD,
    REPOSITORY_CARD,
    REPOSITORY_MANAGER_CARD,
    USER_MANAGER_CARD,
    THEME_SELECTION_CARD
};

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();

  private:
    void _SetupUI();
    void _SetupLayouts();
    void _SetupWidgets();
    void _SetupMemory();

  protected:
    friend class ::MainWindow;
    friend class ::MainWindowConnections;

    // Layouts
    QSharedPointer<QWidget> m_CentralWidget;
    QSharedPointer<QGridLayout> m_ParentLayout;

    // Widgets
    QMap<Cards, QSharedPointer<CardManager>> m_Cards;
    QSharedPointer<ContribCard> m_ContribCard;
    QSharedPointer<RepositoryCard> m_RepositoryCard;
    QSharedPointer<RepositoryManagerCard> m_RepositoryManagerCard;
    QSharedPointer<UserManagerCard> m_UserManagerCard;
    QSharedPointer<ThemeSelectionCard> m_ThemeSelectionCard;
    QSharedPointer<QToolBar> m_ToolBar;
    QSharedPointer<QAction> m_AboutAction;
    QSharedPointer<QMenu> m_LanguageMenu;
    QSharedPointer<QAction> m_LanguageAction;
    QList<QSharedPointer<QAction>> m_LanguageActions;
};
}  // namespace Ui

#endif  // MAINWINDOWUI_HPP