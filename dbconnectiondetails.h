#ifndef DBCONNECTIONDETAILS_H
#define DBCONNECTIONDETAILS_H

#include <QDialog>
#include "dbconnectiondescriptor.h"

namespace Ui {
    class DBConnectionDetails;
}

class DBConnectionDetails : public QDialog
{
    Q_OBJECT

public:
    explicit DBConnectionDetails(QWidget *parent = 0);
    ~DBConnectionDetails();
    void fillForm(DBConnectionDescriptor *descriptor);

private:
    Ui::DBConnectionDetails *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // DBCONNECTIONDETAILS_H
