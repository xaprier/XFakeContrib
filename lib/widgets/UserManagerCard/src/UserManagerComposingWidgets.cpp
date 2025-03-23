#include "UserManagerComposingWidgets.hpp"

#include "XQWidgetComposer.hpp"

using namespace xaprier::Qt::Widgets;

UserManagerComposingWidgets::UserManagerComposingWidgets(QList<QWidget*> list, QWidget* parent) : XQWidgetComposer(list, parent) {
    // Updating This
    this->SetWidgets(list);
}

UserManagerComposingWidgets::~UserManagerComposingWidgets() {
    this->m_List.clear();
}

void UserManagerComposingWidgets::SetWidgets(QList<QWidget*> list) {
    m_List = std::move(list);
    // Updating This
    XQWidgetComposer::SetWidgets(m_List);
    this->Set(this->GetActive());
}

QWidget* UserManagerComposingWidgets::Item(int index) const {
    if (index < 0 || index >= m_List.size()) {
        // todo: error message
        return nullptr;
    }

    return m_List[index];
}

void UserManagerComposingWidgets::Set(int index) {
    if (index < 0 || index >= m_List.size()) {
        // todo: error message
        return;
    }

    this->Show(index);
}