#include "sqleditor.h"
#include <QDebug>
#include <QKeyEvent>

SQLEditor::SQLEditor(QWidget *parent) :
        QTextEdit(parent)
{
}

void SQLEditor::keyPressEvent(QKeyEvent *e) {
    if (e->modifiers()==Qt::ControlModifier && (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)) {
        qDebug()<<"SQLEditor: received control+enter";
        emit controlEnterPressed();
        e->ignore();
    } else {
        QTextEdit::keyPressEvent (e);
    }
}
