#ifndef LOGDIALOG_HPP
#define LOGDIALOG_HPP

#include <QDialog>

#include "../design/ui_LogDialog.h"

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog {
    Q_OBJECT

  public:
    explicit LogDialog(const QString &title = "", const QString text = "", QWidget *parent = nullptr);
    ~LogDialog();

  private:
    Ui::LogDialog *m_Ui;
    QString m_Text;
    QString m_Title;
};

#endif  // LOGDIALOG_HPP
