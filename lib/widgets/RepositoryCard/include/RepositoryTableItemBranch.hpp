#ifndef REPOSITORYTABLEITEMBRANCH_HPP
#define REPOSITORYTABLEITEMBRANCH_HPP

#include <QComboBox>
#include <QPointer>

#include "RepositoryComposingWidgets.hpp"

class RepositoryTableItemBranch final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemBranch)
  public:
    enum class Status {
        COMBOBOX = 0,
    };

    explicit RepositoryTableItemBranch(QWidget *parent = nullptr);
    ~RepositoryTableItemBranch() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

    void UpdateColors() final override {}

  public slots:
    void SetComboBox();
    void Set(Status status);

  private:
    QPointer<QComboBox> m_ComboBox;
};

#endif  // REPOSITORYTABLEITEMBRANCH_HPP