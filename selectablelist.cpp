#include "selectablelist.h"
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>

SelectableList::SelectableList(QWidget *parent) :
    QListWidget(parent)
{
}


void SelectableList::keyPressEvent(QKeyEvent *e) {
    if (e->modifiers()==Qt::ControlModifier && e->key() == Qt::Key_C) {
        QApplication::clipboard()->setText(currentItem()->text());
        e->ignore();
    } else {
        QListWidget::keyPressEvent (e);
    }
}
