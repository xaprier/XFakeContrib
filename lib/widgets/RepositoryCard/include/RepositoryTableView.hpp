#ifndef REPOTABLEVIEW_HPP
#define REPOTABLEVIEW_HPP

#include <qchar.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qevent.h>
#include <qglobal.h>
#include <qtableview.h>
#include <qwidget.h>

#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>

#include "RepositoryTableItem.hpp"
#include "Settings.hpp"

class RepositoryCard;

class RepositoryTableView final : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableView)
  public:
    explicit RepositoryTableView(QWidget *parent = nullptr);
    ~RepositoryTableView() final;
    [[nodiscard]] QList<RepositoryTableItem *> GetItems() const { return m_Items; }

  private:
    friend class RepositoryCardConnections;
    void _ReloadRepositories();

    void _LoadRepositories();
    void _SetupModel();
    void _SetupTable();

  private:
    Settings *m_Settings;
    QStringList m_Repositories;
    QTableView *m_RepoTable;
    QStandardItemModel *m_RepoModel;
    QList<RepositoryTableItem *> m_Items;
    QList<QString> m_ColumnNames{QObject::tr("Enable"), QObject::tr("Repository"), QObject::tr("Branch"), QObject::tr("Remote"), QObject::tr("File"), QObject::tr("Log"), QObject::tr("Push")};
};

#endif  // REPOTABLEVIEW_HPP