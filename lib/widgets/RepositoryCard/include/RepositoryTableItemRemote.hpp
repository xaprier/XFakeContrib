#ifndef REPOSITORYTABLEITEMREMOTE_HPP
#define REPOSITORYTABLEITEMREMOTE_HPP

#include <QLabel>
#include <QPointer>

#include "RepositoryComposingWidgets.hpp"

class RepositoryTableItemRemote final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemRemote)
  public:
    enum class Status {
        LABEL = 0,
    };

    explicit RepositoryTableItemRemote(QWidget *parent = nullptr);
    ~RepositoryTableItemRemote() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

  public slots:
    void SetLabel();
    void Set(Status status);

  private:
    QPointer<QLabel> m_Label;
};

#endif  // REPOSITORYTABLEITEMREMOTE_HPP