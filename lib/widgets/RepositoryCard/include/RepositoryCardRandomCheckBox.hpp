#ifndef REPOSITORYCARDRANDOMCHECKBOX_HPP
#define REPOSITORYCARDRANDOMCHECKBOX_HPP

#include <QCheckBox>
#include <QContextMenuEvent>
#include <QWidget>

#include "Settings.hpp"

class RepositoryCardRandomCheckBox : public QCheckBox {
    Q_OBJECT
  public:
    explicit RepositoryCardRandomCheckBox(QWidget* parent = nullptr);

  protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void showEvent(QShowEvent* event) override;  // we are using this method to set tooltip on startup(promoted widget)

  private:
    Settings* m_Settings;
};

#endif  // REPOSITORYCARDRANDOMCHECKBOX_HPP