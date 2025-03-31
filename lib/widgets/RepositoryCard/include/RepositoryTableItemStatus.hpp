#ifndef REPOSITORYTABLEITEMSTATUS_HPP
#define REPOSITORYTABLEITEMSTATUS_HPP

#include <QPointer>

#include "RepositoryComposingWidgets.hpp"
#include "RepositoryEnableCheckBox.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryTableItemStatus final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemStatus)
  public:
    enum Status {
        CHECKBOX = 0,
        LOADING
    };

    explicit RepositoryTableItemStatus(QWidget *parent = nullptr);
    ~RepositoryTableItemStatus() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

    void UpdateColors() final override;

  public slots:
    void SetLoading();
    void SetCheckBox();
    void Set(Status status);

  private:
    QPointer<xaprier::Qt::Widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<RepositoryEnableCheckBox> m_CheckBox;
};

#endif  // REPOSITORYTABLEITEMSTATUS_HPP