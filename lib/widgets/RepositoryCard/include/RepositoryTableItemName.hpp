#ifndef REPOSITORYTABLEITEMNAME_HPP
#define REPOSITORYTABLEITEMNAME_HPP

#include <QLabel>
#include <QPointer>

#include "RepositoryComposingWidgets.hpp"

class RepositoryTableItemName final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemName)
  public:
    enum class Status {
        LABEL = 0,
    };

    explicit RepositoryTableItemName(QWidget *parent = nullptr);
    ~RepositoryTableItemName() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

  public slots:
    void SetLabel();
    void Set(Status status);

  private:
    QPointer<QLabel> m_Label;
};

#endif  // REPOSITORYTABLEITEMNAME_HPP