#include "dbconnectiondetails.h"
#include "ui_dbconnectiondetails.h"
#include "dbconnectiondescriptor.h"
#include <QDebug>
#include "dbwindow.h"
#include "dbmanager.h"
#include "dbmisc.h"

DBConnectionDetails::DBConnectionDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConnectionDetails)
{
    ui->setupUi(this);

    DBMisc::setWidgetStyleSheet(this);
}

DBConnectionDetails::~DBConnectionDetails()
{
    delete ui;
}

void DBConnectionDetails::fillForm(DBConnectionDescriptor *descriptor) {
    ui->name->setText(descriptor->name);
    ui->host->setText(descriptor->host);
    ui->schema->setText(descriptor->schema);
    ui->user->setText(descriptor->user);
    ui->password->setText(descriptor->password);
    ui->sshHost->setText(descriptor->sshHost);
    ui->sshPassword->setText(descriptor->sshPassword);
    ui->sshUser->setText(descriptor->sshUser);
    ui->sshKeyFile->setText(descriptor->sshKeyFile);
}

void DBConnectionDetails::on_buttonBox_accepted()
{
    DBConnectionDescriptor descriptor;

    descriptor.name = ui->name->text();
    descriptor.host = ui->host->text();
    descriptor.schema = ui->schema->text();
    descriptor.user = ui->user->text();
    descriptor.password = ui->password->text();
    descriptor.sshHost = ui->sshHost->text();
    descriptor.sshPassword = ui->sshPassword->text();
    descriptor.sshUser = ui->sshUser->text();
    descriptor.sshKeyFile = ui->sshKeyFile->text();

    DBManager *manager = DBManager::getInstance();
    manager->setConnectionDescriptor(&descriptor);

}
