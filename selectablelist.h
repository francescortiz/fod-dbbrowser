#ifndef SELECTABLELIST_H
#define SELECTABLELIST_H

#include <QListWidget>

class SelectableList : public QListWidget
{
    Q_OBJECT
public:
    explicit SelectableList(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *e);

signals:

public slots:

};

#endif // SELECTABLELIST_H
