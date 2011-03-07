#include "dbmanager.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include "dbconnectiondescriptor.h"
#include <QSqlError>


bool DBManager::instanceFlag = false;
DBManager* DBManager::instance = NULL;


DBManager::DBManager(QObject *parent) :
    QObject(parent)
{
    DBConnectionDescriptor descriptor;
    QList<DBConnectionDescriptor> storedConnections;
}

DBManager::~DBManager() {
    disconnect();
    instanceFlag = false;
}

DBManager* DBManager::getInstance() {
    if(! instanceFlag) {
        instance = new DBManager();
        instanceFlag = true;
        return instance;
    } else {
        return instance;
    }
}


void DBManager::setConnectionDescriptor(DBConnectionDescriptor *descriptor) {
    this->descriptor.name = descriptor->name;
    this->descriptor.host = descriptor->host;
    this->descriptor.user = descriptor->user;
    this->descriptor.password = descriptor->password;
    this->descriptor.schema = descriptor->schema;
    this->descriptor.sshHost = descriptor->sshHost;
    this->descriptor.sshUser = descriptor->sshUser;
    this->descriptor.sshPassword = descriptor->sshPassword;
    this->descriptor.sshKeyFile = descriptor->sshKeyFile;
}

DBConnectionDescriptor* DBManager::getConnectionDescriptor() {
    return &descriptor;
}

void DBManager::setConnection(QString host, QString user, QString password) {
    descriptor.host = host;
    descriptor.user = user;
    descriptor.password = password;
}

void DBManager::setConnection(QString host, QString user) {
    descriptor.host = host;
    descriptor.user = user;
}

void DBManager::setConnection(QString host) {
    descriptor.host = host;
}

void DBManager::setSSHTunnelCredentials(QString host, QString user, QString password) {
    descriptor.sshHost = host;
    descriptor.sshUser = user;
    descriptor.sshPassword = password;
}

void DBManager::setSSHTunnelCredentials(QString host, QString user) {
    descriptor.sshHost = host;
    descriptor.sshUser = user;
}

void DBManager::setSSHTunnelCredentials(QString host) {
    descriptor.sshHost = host;
}

void DBManager::setSSHTunnelKeyFile(QString host, QString user, QString keyFile) {
    descriptor.sshHost = host;
    descriptor.sshUser = user;
    descriptor.sshKeyFile = keyFile;
}
void DBManager::setSSHTunnelKeyFile(QString host, QString user) {
    descriptor.sshHost = host;
    descriptor.sshUser = user;
}
void DBManager::setSSHTunnelKeyFile(QString host) {
    descriptor.sshHost = host;
}

void DBManager::setSchema(QString schema) {
    if (db.isOpen()) {
        db.close();
    }

    qDebug()<<"DBManager::setSChema() : schema="+schema;
    db.setDatabaseName(schema);
    if (!db.open()) {
        qDebug()<<"...schema could not be changed";
    }

    descriptor.schema = schema;
}

bool DBManager::connect() {
    if (QSqlDatabase::isDriverAvailable("QMYSQL")) {

        db = QSqlDatabase::addDatabase("QMYSQL");
        qDebug()<<"descriptor.host="<<descriptor.host;
        db.setHostName(descriptor.host);
        qDebug()<<"descriptor.schema.size()="<<descriptor.schema.size();
        if (descriptor.schema.size()>0) {
            db.setDatabaseName(descriptor.schema);
        }
        db.setUserName(descriptor.user);
        db.setPassword(descriptor.password);
        if (!db.open()) {
            QMessageBox m;
            QSqlError error = db.lastError();
            m.setText("Unable to connect to database:\n\n"+error.databaseText());
            m.exec();
        } else {
            qDebug()<<"Connected to database";
        }

        return true;

    } else {
        QMessageBox m;
        m.setText("Database driver not available.");
        m.exec();
    }

    return false;
}

bool DBManager::isConnected() {
    return db.isOpen();
}

void DBManager::disconnect() {
    qDebug()<<"DBManager::disconnect()";
    if (db.isOpen()) {
        db.close();
    }
}

QStringList DBManager::getTables() {
    return db.tables();
}

