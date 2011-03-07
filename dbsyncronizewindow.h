#ifndef DBSYNCRONIZEWINDOW_H
#define DBSYNCRONIZEWINDOW_H

#include <QDialog>

namespace Ui {
    class DBSyncronizeWindow;
}

class DBSyncronizeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DBSyncronizeWindow(QWidget *parent = 0);
    ~DBSyncronizeWindow();

private:
    Ui::DBSyncronizeWindow *ui;
};

#endif // DBSYNCRONIZEWINDOW_H
