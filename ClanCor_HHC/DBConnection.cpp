#include "DBConnection.h"
#include <QtGui>
#include <sqlite3.h>
#include <QInputDialog>
#include "GlobalClass.h"
using namespace Globalclass;
bool LastError;
bool debugFlg;

DBConnection::DBConnection()
{
    createConnection();
    q=new QSqlQuery(cn);
    *q = SelectQuery("PRAGMA defaults_cache_size");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
    *q = SelectQuery("PRAGMA synchronous");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
    *q = SelectQuery("PRAGMA page_size");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
    *q = SelectQuery("PRAGMA temp_store");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    if(!DataBaseCommand("PRAGMA default_cache_size=4000"))
    {
        QMessageBox::critical(0,"DataBase","Failed in cahe size set");
    }
    q->clear();
    *q = SelectQuery("PRAGMA default_cache_size");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
    *q = SelectQuery("PRAGMA synchronous");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
    *q = SelectQuery("PRAGMA page_size");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
    *q = SelectQuery("PRAGMA temp_store");
    while(q->next())
    {
//        qDebug()<<q->value(0).toString();
    }
    q->clear();
}

void DBConnection::createConnection()
{
    cn= QSqlDatabase::addDatabase(DB_DRIVER);
    initializeConnections();
}

void DBConnection::openConnection()
{
    cn=QSqlDatabase::database();
}

void DBConnection::closeConnection()
{
    cn.close();
    cn.~QSqlDatabase();
}

QSqlQuery DBConnection::SelectQuery(QString Query)
{
    LastError=false;
    if(cn.isOpen())
    {        
        if(!(q->exec(Query)))
        {            
            QMessageBox::critical(0,"Error",   q->lastError().text());            
            LastError=true;            
            debugInfo(q->lastError().text());
        }
        if(debugFlg) debugInfo(Query);
    }
    else
    {
        QMessageBox::critical(0,"DataBase", "DB Connection Closed" );
        LastError=true;
    }
    return *q;
}

bool DBConnection::initializeConnections()
{
    try
    {
        LastError=false;        
        cn.setDatabaseName(DB_DBNAME);
        if ( ! cn.open() ) {
            LastError=true;
            QMessageBox::critical(0,"DataBase", "Cannot open database:"+ cn.lastError().text());
            return FALSE;
        }
        return TRUE;
    }
    catch(...)
    {
        LastError=true;
        QMessageBox::critical(0,"DataBase", "Query Execution Failed" );
        return FALSE;
    }
}
bool DBConnection::DataBaseCommand(QString StrQuery)
{
    LastError=false;

    if(cn.isOpen())
    {
        q->clear();
        if(!(q->exec(StrQuery)))
        {
            LastError=true;
            if(q->lastError().number()!=19)
            {
                QMessageBox::critical(0,"DataBase",   q->lastError().text());
                debugInfo(q->lastError().text());
                debugInfo(StrQuery);                
                q->clear();
                return false;
            }
            else
            {
                QVariant v = q->driver()->handle();
                if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*")==0)
                {
                    sqlite3 *handle = *static_cast<sqlite3 **>(v.data());
                    if (handle != 0)
                    {
                        qDebug()<<"Error: " + QString(sqlite3_errmsg(handle));
                        QMessageBox::about(0,"Trigger",sqlite3_errmsg(handle));
                    }
                }
                debugInfo(q->lastError().text());
                debugInfo(StrQuery);
                q->clear();
                return false;
            }
        }
        if(q->isActive()==false)
        {
            QVariant v = q->driver()->handle();
            if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*")==0)
            {
                sqlite3 *handle = *static_cast<sqlite3 **>(v.data());
                if (handle != 0)
                {
                    qDebug()<<"Error: "+ QString(sqlite3_errmsg(handle));
                    QMessageBox::about(0,"Trigger",sqlite3_errmsg(handle));
                }
            }
            QMessageBox::about(0,"Trigger",q->lastError().text());
            debugInfo(q->lastError().text());
            debugInfo(StrQuery);
        }
    }
    else
    {
        LastError=true;
        QMessageBox::critical(0,"DataBase", "DB Connection Closed" );
    }
    if(debugFlg) debugInfo(StrQuery);
    q->clear();
    return true;
}

bool DBConnection::DataBaseCommand(QSqlQuery SqlQuery)
{    
    LastError=false;
    if(cn.isOpen())
    {
        if(!(SqlQuery.exec()))
        {
            LastError=true;
            QMessageBox::critical(0,"DataBase",   SqlQuery.lastError().text());
            debugInfo(SqlQuery.lastError().text());
            debugInfo(SqlQuery.executedQuery());
            SqlQuery.clear();
        }
    }
    else
    {
        SqlQuery.clear();
        LastError=true;
        QMessageBox::critical(0,"DataBase", "DB Connection Closed" );
    }
    if(debugFlg) debugInfo(SqlQuery.executedQuery());
    SqlQuery.clear();
    return true;
}

bool DBConnection::IsLastError()
{
    if(LastError) return true;
    else return false;
}

int DBConnection::Size(QSqlQuery query)
{
    int size=0;
    while(query.next())
    {
        size++;
    }
    query.clear();
    return size;
}

void DBConnection::clearAll()
{
    q->clear();
}

void DBConnection::debugInfo(QVariant info)
{
    if(debugFlg)
    {
        qDebug()<<info.toString();
    }
}
