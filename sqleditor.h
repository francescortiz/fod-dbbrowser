#ifndef SQLEDITOR_H
#define SQLEDITOR_H

#include <QTextEdit>

class SQLEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit SQLEditor(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *e);

signals:
    void controlEnterPressed();

public slots:

};

#endif // SQLEDITOR_H
