#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDriver>

#define DB_DRIVER   "QSQLITE"
#define LOCAL_PATH 1
//#define HHD_PATH 1
#ifdef LOCAL_PATH
#define PATH QDir::currentPath()
#define DB_DBNAME   "DEMODB"
#elif defined(HHD_PATH)
#define PATH (QString)"/mnt"
#define DB_DBNAME   "/DEMODB"
#endif

extern bool debugFlg;

class DBConnection
{
    public:
        QSqlDatabase cn;
        DBConnection();
        QSqlQuery *q;
        void createConnection();
        void openConnection();
        void closeConnection();
        bool initializeConnections();
        bool IsLastError();
        QSqlQuery SelectQuery(QString Query);
        bool DataBaseCommand(QString Query);
        bool DataBaseCommand(QSqlQuery SqlQuery);
        int Size(QSqlQuery);
        void clearAll();
        void debugInfo(QVariant info);
};

#endif // DBCONNECTION_H
