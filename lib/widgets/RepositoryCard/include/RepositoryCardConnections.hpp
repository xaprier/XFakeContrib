#ifndef REPOSITORYCARDCONNECTIONS_HPP
#define REPOSITORYCARDCONNECTIONS_HPP

#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QObject>

#include "RepositoryTableView.hpp"
#include "Settings.hpp"

#include "Widgets_Global.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class RepositoryCardUI;
}
QT_END_NAMESPACE

// Forward declaration for item
class RepositoryTableItem;
class RepositoryCard;

class WIDGETS_EXPORT RepositoryCardConnections final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCardConnections)
  public:
    explicit RepositoryCardConnections(QList<RepositoryTableItem *> items, Ui::RepositoryCardUI *ui, QPointer<RepositoryTableView> tableView, QObject *base = nullptr);
    ~RepositoryCardConnections() final;

  signals:
    void si_PushesCompleted(bool success);

  public slots:
    void sl_RepositoriesUpdated();

  protected slots:
    void sl_CreateCommitsButtonClicked(bool checked);
    void sl_PushButtonClicked(bool checked);
    void sl_CommitCountCBStateChanged(int state);
    void sl_DateCBStateChanged(int state);
    void sl_CommitMessageCBStateChanged(int state);
    void sl_CommitContentCBStateChanged(int state);

    void sl_StartDateChanged(QDate date);
    void sl_EndDateChanged(QDate date);

    void sl_CommitterFinished(bool success);
    void sl_AllCommittersFinished(bool success);

    void sl_ItemPushCompleted(QFutureWatcher<void> *watcher);

  private:
    void _SetupConnections();
    void _SetupDates();
    void _WidgetsSetEnabled(bool enabled);
    void _UpdateButtonsStatus();

    [[nodiscard]] quint32 _GetCommitCount() const;
    [[nodiscard]] QString _GetCommitMessage() const;
    [[nodiscard]] QString _GetCommitContent() const;

    void _CreateCommits(QList<RepositoryTableItem *> &enabledItems, const QDate &startDate, const QDate &endDate);

  private:
    friend class RepositoryCard;

    QList<QFutureWatcher<void> *> m_PushWatchers;
    QList<RepositoryTableItem *> m_Items;
    QPointer<RepositoryTableView> m_TableView;
    Ui::RepositoryCardUI *m_Ui;
    Settings *m_Settings;
};

#endif  // REPOSITORYCARDCONNECTIONS_HPP