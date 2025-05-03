#include "RepositoryCardRandomCheckBox.hpp"

#include <QInputDialog>

RepositoryCardRandomCheckBox::RepositoryCardRandomCheckBox(QWidget* parent) : QCheckBox(parent), m_Settings(Settings::Instance()) {
}

void RepositoryCardRandomCheckBox::contextMenuEvent(QContextMenuEvent* event) {
    bool ok = false;
    Settings* settings = Settings::Instance();

    int dValue = settings->GetDefaultRandomMax();

    int value = QInputDialog::getInt(this,
                                     QObject::tr("Set Max Random Count"),
                                     QObject::tr("Maximum Random Count:"),
                                     dValue,  // default value
                                     1,       // min
                                     1000,    // max
                                     1,       // step
                                     &ok);

    if (ok) {
        settings->SetRandomMax(value);
        this->setToolTip(QObject::tr("Random count between [1,%1]\nYou can set the maximum random count with right click").arg(value));
    } else {
        // User canceled the input dialog
        event->ignore();
        return;
    }

    event->accept();
}

void RepositoryCardRandomCheckBox::showEvent(QShowEvent* event) {
    QCheckBox::showEvent(event);

    // we will set the tooltip only once
    static bool firstShow = true;
    if (!firstShow) {
        return;
    }
    firstShow = false;

    int maxRandCount = m_Settings->GetRandomMax();

    this->setToolTip(QObject::tr("Random count between [1,%1]\nYou can set the maximum random count with right click").arg(maxRandCount));
}
