#include "ContribCardInfo.hpp"
ContribCardInfo::ContribCardInfo(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle(QObject::tr("Contribution Card Information"));
    this->setMinimumWidth(800);
    this->setMinimumHeight(300);
    this->_SetupUI();
}

ContribCardInfo::~ContribCardInfo() {
}

void ContribCardInfo::_SetupUI() {
    this->_SetupMemory();
    this->_SetupConnections();
    this->_SetupLayout();
    this->_SetupTextBrowser();
}

void ContribCardInfo::_SetupMemory() {
    m_TextBrowser = QSharedPointer<QTextBrowser>(new QTextBrowser(this));
    m_Layout = QSharedPointer<QGridLayout>(new QGridLayout(this));
    m_ButtonBox = QSharedPointer<QDialogButtonBox>(new QDialogButtonBox(this));
}

void ContribCardInfo::_SetupConnections() {
    connect(m_ButtonBox.data(), &QDialogButtonBox::accepted, this, &ContribCardInfo::accept);
    connect(m_ButtonBox.data(), &QDialogButtonBox::rejected, this, &ContribCardInfo::reject);
}

void ContribCardInfo::_SetupLayout() {
    m_ButtonBox->addButton(QDialogButtonBox::Ok);
    m_ButtonBox->addButton(QDialogButtonBox::Cancel);
    m_Layout->addWidget(m_TextBrowser.data(), 0, 0, 1, 2);
    m_Layout->addWidget(m_ButtonBox.data(), 1, 1, 1, 1);
    this->setLayout(m_Layout.data());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_TextBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ContribCardInfo::_SetupTextBrowser() {
    m_TextBrowser->setOpenExternalLinks(true);
    m_TextBrowser->setHtml(
        "<p align=\"center\">"
        "<h2>How To Use Contribution Card</h2><br />"
        "In Contribution Card, you can see the list of all the contributions made by the user you defined in the <b>User Manager Card</b>.<br />"
        "You can hover the days in Contribution Card to see how many contribution made by the user.<br /><br />"
        "Additionally you can use Contribution Card to set dates in <b>Repository Card</b> as;"
        "<b><ul>"
        "<li>Mouse Left Click » Set Start Date</li>"
        "<li>Mouse Right Click » Set End Date</li>"
        "<li>Mouse Middle Click » Set Start Date and End Date</li>"
        "</ul></b>"
        "<br />");
}
