#include "LogDialog.hpp"

LogDialog::LogDialog(QString title, QString text, QWidget *parent) : QDialog(parent),
                                                                     m_Ui(new Ui::LogDialog),
                                                                     m_Text(std::move(text)),
                                                                     m_Title(std::move(title)) {
    m_Ui->setupUi(this);
    m_Ui->groupBox->setTitle(m_Title);
    m_Ui->logTextBrowser->setText(m_Text);
}

LogDialog::~LogDialog() {
    delete m_Ui;
}
