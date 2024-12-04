#include "LogDialog.hpp"

LogDialog::LogDialog(const QString &title, const QString text, QWidget *parent) : QDialog(parent),
                                                                                  m_Ui(new Ui::LogDialog),
                                                                                  m_Text(text),
                                                                                  m_Title(title) {
    m_Ui->setupUi(this);
    m_Ui->groupBox->setTitle(m_Title);
    m_Ui->logTextBrowser->setText(m_Text);
}

LogDialog::~LogDialog() {
    delete m_Ui;
}
