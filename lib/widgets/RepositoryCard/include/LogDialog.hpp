#ifndef LOGDIALOG_HPP
#define LOGDIALOG_HPP

#include <QDialog>

#include "../design/ui_LogDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LogDialog;
}
QT_END_NAMESPACE

class LogDialog final : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LogDialog)
  public:
    explicit LogDialog(QString title = "", QString text = "", QWidget* parent = nullptr);
    ~LogDialog() final;

  private:
    Ui::LogDialog* m_Ui;
    QString m_Text;
    QString m_Title;
};

#endif  // LOGDIALOG_HPP
