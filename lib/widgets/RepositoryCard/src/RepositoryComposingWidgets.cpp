#include "RepositoryComposingWidgets.hpp"

#include "XQWidgetComposer.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryComposingWidgets::RepositoryComposingWidgets(QList<QWidget*> list, QWidget* parent) : XQWidgetComposer(list, parent) {
    // Updating This
    this->SetWidgets(list);
}

RepositoryComposingWidgets::~RepositoryComposingWidgets() {
    this->m_List.clear();
}

void RepositoryComposingWidgets::SetWidgets(QList<QWidget*> list) {
    m_List = std::move(list);
    // Updating This
    XQWidgetComposer::SetWidgets(m_List);
    this->Set(this->GetActive());
}

QWidget* RepositoryComposingWidgets::Item(int index) const {
    if (index < 0 || index >= m_List.size()) {
        // todo: error message
        return nullptr;
    }

    return m_List[index];
}

void RepositoryComposingWidgets::Set(int index) {
    if (index < 0 || index >= m_List.size()) {
        // todo: error message
        return;
    }

    this->Show(index);
}