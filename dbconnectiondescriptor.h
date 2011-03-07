#ifndef DBCONNECTIONDESCRIPTOR_H
#define DBCONNECTIONDESCRIPTOR_H

#include <QMetaType>

class DBConnectionDescriptor
{

public:
    DBConnectionDescriptor();
    //DBConnectionDescriptor(const DBConnectionDescriptor& src);
    QString name;
    QString host;
    QString user;
    QString password;
    QString schema;
    QString sshHost;
    QString sshUser;
    QString sshPassword;
    QString sshKeyFile;

    DBConnectionDescriptor clone();

signals:

public slots:

};

Q_DECLARE_METATYPE(DBConnectionDescriptor);
Q_DECLARE_METATYPE(QList<DBConnectionDescriptor>);

#endif // DBCONNECTIONDESCRIPTOR_H
