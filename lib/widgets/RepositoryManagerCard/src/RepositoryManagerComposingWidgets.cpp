#include "RepositoryManagerComposingWidgets.hpp"

#include "XQWidgetComposer.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryManagerComposingWidgets::RepositoryManagerComposingWidgets(QList<QWidget*> list, QWidget* parent) : XQWidgetComposer(list, parent) {
    // Updating This
    this->SetWidgets(list);
}

RepositoryManagerComposingWidgets::~RepositoryManagerComposingWidgets() {
    this->m_List.clear();
}

void RepositoryManagerComposingWidgets::SetWidgets(QList<QWidget*> list) {
    m_List = std::move(list);
    // Updating This
    XQWidgetComposer::SetWidgets(m_List);
    this->Set(this->GetActive());
}

QWidget* RepositoryManagerComposingWidgets::Item(int index) const {
    if (index < 0 || index >= m_List.size()) {
        // todo: error message
        return nullptr;
    }

    return m_List[index];
}

void RepositoryManagerComposingWidgets::Set(int index) {
    if (index < 0 || index >= m_List.size()) {
        // todo: error message
        return;
    }

    this->Show(index);
}