#include "sqleditor.h"
#include <QDebug>
#include <QKeyEvent>

SQLEditor::SQLEditor(QWidget *parent) :
        QTextEdit(parent)
{
}

bool controlPressed = false;

void SQLEditor::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Control) {
        controlPressed = true;
        QTextEdit::keyPressEvent (e);
    } else if (controlPressed && (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)) {
        qDebug()<<"SQLEditor: received control+enter";
        emit controlEnterPressed();
        e->ignore ();
    } else {
        QTextEdit::keyPressEvent (e);
    }
}
void SQLEditor::keyReleaseEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Control) {
        controlPressed = false;
    }
    QTextEdit::keyPressEvent (e);
}
