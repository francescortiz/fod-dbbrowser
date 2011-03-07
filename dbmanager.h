#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include "dbconnectiondescriptor.h"

class DBManager : public QObject
{
    Q_OBJECT
public:
    ~DBManager();

// Connection fucntions
    void setConnectionDescriptor(DBConnectionDescriptor *descriptor);
    void setConnection(QString host, QString user, QString password);
    void setConnection(QString host, QString user);
    void setConnection(QString host);
    void setSSHTunnelCredentials(QString host, QString user, QString password);
    void setSSHTunnelCredentials(QString host, QString user);
    void setSSHTunnelCredentials(QString host);
    void setSSHTunnelKeyFile(QString host, QString user, QString keyFile);
    void setSSHTunnelKeyFile(QString host, QString user);
    void setSSHTunnelKeyFile(QString host);
    // Schemas
    void setSchema(QString schema);
    QList<QString> getSchemas();
    // connect() should prompt for any missing data
    bool connect();
    bool isConnected();
    void disconnect();
    DBConnectionDescriptor* getConnectionDescriptor();
    QStringList getTables();

    QList<DBConnectionDescriptor> storedConnections;

    static DBManager* getInstance();

// Query functions

private:
    explicit DBManager(QObject *parent = 0);

    DBConnectionDescriptor descriptor;
    QSqlDatabase db;

    static bool instanceFlag;
    static DBManager *instance;


signals:

public slots:

};

#endif // DBMANAGER_H
