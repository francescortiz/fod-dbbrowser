/*

Drag and drop should drop SQL text on text boxes and .sql files on filesystem folders.
The application should allow you to perform drag and drop of everything. Drag a table into another database, drag a row onto another table, cut, copy and paste elements, drag users, etc.
Also, foreign key references should be easily accessible without loosing the view we have. (¿nested treeviews in table cells? ¿Apple's Finder like column navigation?)
In case the destination element exists it should ask for type of operation: add new elements, synchronize elements or discard target data. It should work at row, table and database level and others (¿users?)
It should also give better information on error 150 (foreign key exceptions).

*/

#include "dbwindow.h"
#include "ui_dbwindow.h"
#include "dbconnectiondetails.h"
#include "ui_dbconnectiondetails.h"
#include "dbmanager.h"
#include <QDebug>
#include "sqlsyntaxhighlighter.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSettings>
#include "dbconnectiondescriptor.h"
#include <QVariant>
#include "dbmisc.h"

DBManager *DBWindow::manager = DBManager::getInstance();

DBWindow::DBWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DBWindow)
{
    ui->setupUi(this);

    QSettings settings("fod", "fod-dbbrowser");
    int width = settings.value("width").toInt();
    int height = settings.value("height").toInt();
    resize(width, height);

    int size = settings.beginReadArray("connections");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        DBConnectionDescriptor dbcd;
        dbcd.name = settings.value("name").toString();
        dbcd.host = settings.value("host").toString();
        dbcd.user = settings.value("user").toString();
        dbcd.password = settings.value("password").toString();
        dbcd.schema = settings.value("schema").toString();
        dbcd.sshHost = settings.value("sshHost").toString();
        dbcd.sshUser = settings.value("sshUser").toString();
        dbcd.sshPassword = settings.value("sshPassword").toString();
        dbcd.sshKeyFile = settings.value("sshKeyFile").toString();
        ui->storedConnections->addItem(dbcd.name+" ("+dbcd.user+"@"+dbcd.host+"/"+dbcd.schema+")", qVariantFromValue(dbcd));
    }
    settings.endArray();
    highlighter = new SQLSyntaxHighlighter(ui->sqlEdit->document());

    setWindowTitle("fod-dbbrowser");

    ui->tableContent->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->sqlOutput->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    consolidateDisconnection();

    DBMisc::setWidgetStyleSheet(this);
}

DBWindow::~DBWindow()
{
    qDebug()<<"Destroying main window";
    manager->disconnect();

    QSettings settings("fod", "fod-dbbrowser");
    settings.setValue("width", width());
    settings.setValue("height", height());


    settings.beginWriteArray("connections");
    int offset = 0;
    qDebug()<<"Items in stored connections = "<<ui->storedConnections->count();
    for (int i = 0; i < ui->storedConnections->count(); i++) {
        QVariant var = ui->storedConnections->itemData(i);
        DBConnectionDescriptor dbcd = var.value< DBConnectionDescriptor >();
        if (var.isValid() && dbcd.name.size()>0) {
            settings.setArrayIndex(i-offset);
            settings.setValue("name", dbcd.name);
            settings.setValue("host", dbcd.host);
            settings.setValue("user", dbcd.user);
            settings.setValue("password", dbcd.password);
            settings.setValue("schema", dbcd.schema);
            settings.setValue("sshHost", dbcd.sshHost);
            settings.setValue("sshUser", dbcd.sshUser);
            settings.setValue("sshPassword", dbcd.sshPassword);
            settings.setValue("sshKeyFile", dbcd.sshKeyFile);
        } else {
            offset++;
        }
    }
    settings.endArray();

    delete ui;
}

void DBWindow::resizeEvent(QResizeEvent *) {
    //ui->mainLayout->setGeometry(QRect(0,0,ui->centralWidget->width(), ui->centralWidget->height()));
}


void DBWindow::setTitle(DBConnectionDescriptor *dbcd) {
    setWindowTitle(dbcd->name+" ("+dbcd->user+"@"+dbcd->host+"/"+dbcd->schema+") - fod-dbbrowser");
}

void DBWindow::consolidateConnection() {
    DBConnectionDescriptor *acd = manager->getConnectionDescriptor();
    setTitle(acd);
    ui->connectButton->setText("Disconnect");

    ui->schemaList->setEnabled(true);
    ui->tableList->setEnabled(true);
    ui->tabs->setEnabled(true);
    ui->sqlGroupBox->setEnabled(true);

    QSqlQuery query;
    query.exec("SHOW DATABASES");
    ui->schemaList->clear();
    ui->schemaList->addItem("<Select schema>");
    while (query.next()) {
        ui->schemaList->addItem(query.value(0).toString());
    }

    if (ui->schemaList->findText(acd->schema)!=-1) {
        ui->schemaList->setCurrentIndex( ui->schemaList->findText(acd->schema) );
    }

    // We are going to add the connection to stored connections
    if (acd->name.size()>0) {
        // First we check if the connection is already listed in stored connections, and delete it
        bool exists = false;
        for (int i = 0; i < ui->storedConnections->count(); i++) {
            QVariant var = ui->storedConnections->itemData(i);
            if (var.isValid()) {
                DBConnectionDescriptor dbcd = var.value< DBConnectionDescriptor >();
                if (dbcd.name == acd->name) {
                    ui->storedConnections->setItemData(i, qVariantFromValue(acd->clone()));
                    ui->storedConnections->setItemText(i, acd->name+" ("+acd->user+"@"+acd->host+"/"+acd->schema+")");
                    exists = true;
                    break;
                }
            }
        }
        if (!exists) {
            ui->storedConnections->addItem(
                    acd->name+" ("+acd->user+"@"+acd->host+"/"+acd->schema+")",
                    qVariantFromValue(acd->clone())
                    );
        }
    }

    for (int i = 0; i < ui->storedConnections->count(); i++) {
        QVariant var = ui->storedConnections->itemData(i);
        if (var.isValid()) {
            DBConnectionDescriptor dbcd = var.value< DBConnectionDescriptor >();
            if (
                    dbcd.name == acd->name
                    &&
                    i != ui->storedConnections->currentIndex()
                    ) {
                ui->storedConnections->setCurrentIndex(i);
                break;
            }
        }
    }

}

void DBWindow::consolidateDisconnection() {
    setWindowTitle("fod-dbbrowser");
    ui->connectButton->setText("Connect manually");

    ui->schemaList->clear();
    ui->schemaList->addItem("<Select schema>");

    ui->schemaList->setEnabled(false);
    ui->tableList->setEnabled(false);
    ui->tabs->setEnabled(false);
    ui->sqlGroupBox->setEnabled(false);


    ui->storedConnections->setCurrentIndex(0);

}

void DBWindow::on_connectButton_clicked()
{
    if (manager->isConnected()) {
        manager->disconnect();
        consolidateDisconnection();
    } else {
        DBConnectionDetails details;
        details.fillForm(manager->getConnectionDescriptor());
        if (details.exec()) {
            qDebug()<<"Ha fet ok";
            manager->connect();
            if (manager->isConnected()) {
                consolidateConnection();
            } else {
                on_connectButton_clicked();
            }
        } else {
            qDebug()<<"Ha fet cancel";
        }
    }
}


void DBWindow::on_schemaList_currentIndexChanged(QString schema)
{
    QSqlQuery query;
    if (schema.size() && schema.mid(0,1)!=QString("<")) {
        manager->setSchema(schema);
    }
    query.exec("SHOW TABLES IN "+schema);
    ui->tableList->selectionModel()->reset();
    ui->tableList->clear();
    while (query.next()) {
        ui->tableList->addItem(query.value(0).toString());
    }
}

void DBWindow::on_tableList_currentRowChanged(int )
{
    QString table = ui->tableList->currentItem()->text();
    qDebug()<<"Selected table = "<<table;

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable(table);
    model->select();
    ui->tableContent->setModel(model);

    ui->tabs->setCurrentIndex(0);

}


void DBWindow::on_sqlEdit_controlEnterPressed()
{
    QString sql = ui->sqlEdit->toPlainText();
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(sql);
    ui->sqlOutput->setModel(model);
    QSqlError error =model->lastError();
    if (error.number()!=-1) {
        QMessageBox m;
        m.setText(QString(error.driverText())+"\n"+QString(error.databaseText()));
        m.exec();
    }
    ui->tabs->setCurrentIndex(1);

}

void DBWindow::on_storedConnections_currentIndexChanged(int index)
{
    QVariant var = ui->storedConnections->itemData(index);
    if (var.isValid()) {

        DBConnectionDescriptor dbcd = var.value< DBConnectionDescriptor >();

        qDebug()<<"dbcd.name = "<<dbcd.name;

        if (dbcd.name != manager->getConnectionDescriptor()->name) {

            manager->disconnect();

            manager->setConnectionDescriptor(&dbcd);

            manager->connect();
            if (manager->isConnected()) {
                consolidateConnection();
            } else {
                consolidateDisconnection();
            }
        }

    }
}

void DBWindow::on_removeConnection_clicked()
{
    int index = ui->storedConnections->currentIndex();
    QVariant var = ui->storedConnections->itemData(index);
    if (var.isValid()) {

        DBConnectionDescriptor dbcd = var.value< DBConnectionDescriptor >();

        if (dbcd.name.size()>0) {
            ui->storedConnections->setCurrentIndex(0);
            ui->storedConnections->removeItem(index);
        }

    }
}
