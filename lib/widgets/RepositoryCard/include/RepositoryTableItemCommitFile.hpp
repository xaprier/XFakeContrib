#ifndef REPOSITORYTABLEITEMCOMMITFILE_HPP
#define REPOSITORYTABLEITEMCOMMITFILE_HPP

#include <QPointer>
#include <QToolButton>

#include "RepositoryComposingWidgets.hpp"

class RepositoryTableItemCommitFile final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemCommitFile)
  public:
    enum class Status {
        BUTTON = 0,
    };

    explicit RepositoryTableItemCommitFile(QWidget *parent = nullptr);
    ~RepositoryTableItemCommitFile() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }
    void SetValidFileSelected(bool selected);

  public slots:
    void SetButton();
    void Set(Status status);

  private:
    QPointer<QToolButton> m_Button;
};

#endif  // REPOSITORYTABLEITEMCOMMITFILE_HPP