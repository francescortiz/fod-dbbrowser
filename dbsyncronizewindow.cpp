#include "dbsyncronizewindow.h"
#include "ui_dbsyncronizewindow.h"

DBSyncronizeWindow::DBSyncronizeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBSyncronizeWindow)
{
    ui->setupUi(this);
}

DBSyncronizeWindow::~DBSyncronizeWindow()
{
    delete ui;
}
