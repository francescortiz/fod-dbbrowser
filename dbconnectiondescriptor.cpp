#include "dbconnectiondescriptor.h"

DBConnectionDescriptor::DBConnectionDescriptor()
{
}

/*
DBConnectionDescriptor::DBConnectionDescriptor(const DBConnectionDescriptor& src)
{
    name        = src.name;
    host        = src.host;
    user        = src.user;
    password    = src.password;
    schema      = src.schema;
    sshHost     = src.sshHost;
    sshUser     = src.sshUser;
    sshPassword = src.sshPassword;
    sshKeyFile  = src.sshKeyFile;
}
*/

DBConnectionDescriptor DBConnectionDescriptor::clone() {
    DBConnectionDescriptor dbcd;
    dbcd.name = name;
    dbcd.host = host;
    dbcd.user = user;
    dbcd.password = password;
    dbcd.schema = schema;
    dbcd.sshHost = sshHost;
    dbcd.sshUser = sshUser;
    dbcd.sshPassword = sshPassword;
    dbcd.sshKeyFile = sshKeyFile;

    return dbcd;

}
