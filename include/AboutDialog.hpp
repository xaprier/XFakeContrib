#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>
#include <QIcon>

#include "../design/ui_AboutDialog.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog {
    Q_OBJECT

  public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

  private:
    Ui::AboutDialog *m_Ui;
};

#endif  // ABOUTDIALOG_HPP
