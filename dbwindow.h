#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QMainWindow>
#include "dbconnectiondescriptor.h"
#include "dbmanager.h"
#include "sqlsyntaxhighlighter.h"
#include <QSettings>

namespace Ui {
    class DBWindow;
}

class DBWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBWindow(QWidget *parent = 0);
    ~DBWindow();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::DBWindow *ui;
    void consolidateConnection();
    void consolidateDisconnection();
    SQLSyntaxHighlighter *highlighter;

    static DBManager* manager;

private slots:
    void on_removeConnection_clicked();
    void on_storedConnections_currentIndexChanged(int index);
    void on_sqlEdit_controlEnterPressed();
    void on_tableList_currentRowChanged(int currentRow);
    void on_schemaList_currentIndexChanged(QString );
    void on_connectButton_clicked();
    void setTitle(DBConnectionDescriptor *dbcd);
};

#endif // DBWINDOW_H
