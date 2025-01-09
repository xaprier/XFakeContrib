#ifndef REPOSITORYENABLECHECKBOX_HPP
#define REPOSITORYENABLECHECKBOX_HPP

#include <qglobal.h>

#include <QCheckBox>
#include <QWidget>

class RepositoryEnableCheckBox final : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryEnableCheckBox)
  public:
    explicit RepositoryEnableCheckBox(QWidget *parent = nullptr);
    ~RepositoryEnableCheckBox() override = default;

    [[nodiscard]] bool IsChecked() const { return m_CheckBox->isChecked(); }

  signals:
    void stateChanged(int state);

  protected:
    void mousePressEvent(QMouseEvent *event) override;

  private:
    QCheckBox *m_CheckBox;
};

#endif  // REPOSITORYENABLECHECKBOX_HPP