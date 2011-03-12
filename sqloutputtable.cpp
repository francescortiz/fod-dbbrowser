#include "sqloutputtable.h"
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QModelIndex>

SQLOutputTable::SQLOutputTable(QWidget *parent) :
    QTableView(parent)
{
}

void SQLOutputTable::keyPressEvent(QKeyEvent *e) {
    if (e->modifiers()==Qt::ControlModifier && e->key() == Qt::Key_C) {
        QString selectedText = "";
        for (int i = 0; i < selectedIndexes().size(); i++) {
            QModelIndex index = selectedIndexes().at(i);
            selectedText += index.data().toString() + "\n";
        }
        QApplication::clipboard()->setText(selectedText);
        e->ignore();
    } else {
        QTableView::keyPressEvent (e);
    }
}
