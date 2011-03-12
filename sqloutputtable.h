#ifndef SQLOUTPUTATABLE_H
#define SQLOUTPUTATABLE_H

#include <QTableView>

class SQLOutputTable : public QTableView
{
    Q_OBJECT
public:
    explicit SQLOutputTable(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *e);

signals:

public slots:

};

#endif // SQLOUTPUTATABLE_H
