#ifndef CONTRIBCARDINFO_HPP
#define CONTRIBCARDINFO_HPP

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QSharedPointer>
#include <QTextBrowser>

class ContribCardInfo : public QDialog {
    Q_OBJECT
  public:
    explicit ContribCardInfo(QWidget *parent = nullptr);
    ~ContribCardInfo();

  private:
    void _SetupUI();
    void _SetupMemory();
    void _SetupConnections();
    void _SetupLayout();
    void _SetupTextBrowser();

  private:
    QSharedPointer<QTextBrowser> m_TextBrowser;
    QSharedPointer<QGridLayout> m_Layout;
    QSharedPointer<QDialogButtonBox> m_ButtonBox;
};

#endif  // CONTRIBCARDINFO_HPPc