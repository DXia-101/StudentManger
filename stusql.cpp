#include "stusql.h"
#include "qapplication.h"
#include <QSqlQuery>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlError>

stusql * stusql::ptrstuSql = nullptr;

stusql::stusql(QObject *parent)
    : QObject{parent}
{

//    StuInfo s;
//    s.name = "小爪";
//    for(int i = 0;i < 10;++i){
//        addStu(s);
//    }
//    getStuCnt();
//    getPageStu(2,3);
//    delStu(18);
//    StuInfo s;
//    s.name = "dd";
//    s.id = 8;
//    UpdateStuInfo(s);

    UserInfo info;
    info.username = "xiaoyu";
    info.password = "123456";
    info.aut = "admin";
    AddUser(info);
    AddUser(info);
    auto l = getAllUser();
    qDebug()<<isExit("xiaoyu");
    info.password = "666";
    UpdateUser(info);
    delUser("xiaoyu");
}

void stusql::init()
{
    if (QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
#if 0
    auto str = QCoreApplication::applicationDirPath()+"data.db";
    qDebug()<<str;
#endif
    m_db.setDatabaseName("E:\\data.db");
    if (!m_db.open())
        qDebug()<<"Unable to open database";

}

quint32 stusql::getStuCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("SELECT COUNT(id) FROM student;");
    quint32 uiCnt = 0;
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<StuInfo> stusql::getPageStu(quint32 page, quint32 uiCnt)
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("SELECT * FROM student ORDER BY id LIMIT %1 OFFSET %2;")
            .arg(uiCnt).arg(page*uiCnt);
    sql.exec(strsql);
    StuInfo info;
    while(sql.next()){
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.age = sql.value(2).toUInt();
        info.grade = sql.value(3).toUInt();
        info.uiclass = sql.value(4).toUInt();
        info.studentid = sql.value(5).toUInt();
        info.phone = sql.value(6).toString();
        info.wechat = sql.value(7).toString();
        l.push_back(info);
    }
    return l;
}

bool stusql::addStu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("INSERT INTO student VALUES (NULL,'%1',%2,%3,%4,%5,'%6','%7')")
            .arg(info.name)
            .arg(info.age)
            .arg(info.grade)
            .arg(info.uiclass)
            .arg(info.studentid)
            .arg(info.phone)
            .arg(info.wechat);
    qDebug()<<sql.exec(strSql);
}

bool stusql::delStu(int id)
{
    QSqlQuery sql(m_db);

    return sql.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
}

bool stusql::clearStuTable()
{
    QSqlQuery sql(m_db);
    sql.exec(QString("DELETE FROM student"));
    return sql.exec(QString("DELETE FROM sqlite_sequence WHERE name = 'student'"));
}

bool stusql::UpdateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("UPDATE student SET name='%1',age=%2,grade=%3,uiclass=%4,"
                             "studentid=%5,phone='%6',wechat='%7' where id=%8")
            .arg(info.name)
            .arg(info.age)
            .arg(info.grade)
            .arg(info.uiclass)
            .arg(info.studentid)
            .arg(info.phone)
            .arg(info.wechat)
            .arg(info.id);
    qDebug()<<strSql;
    if(!sql.exec(strSql)){
        QSqlError error = sql.lastError();
        qDebug()<< error.text();
    }
}

QList<UserInfo> stusql::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);
    sql.exec("SELECT * FROM username");
    UserInfo info;
    while(sql.next()){
        info.username = sql.value(0).toString();
        info.password = sql.value(1).toString();
        info.aut = sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool stusql::isExit(QString strUser)
{
    QSqlQuery sql(m_db);

    sql.exec(QString("SELECT * FROM username WHERE username='%1';").arg(strUser));
    return sql.next();
}

bool stusql::UpdateUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("UPDATE username SET password='%1',auth='%2' WHERE username = '%3'")
            .arg(info.password)
            .arg(info.aut)
            .arg(info.username);
    if(!sql.exec(strSql)){
        QSqlError error = sql.lastError();
        qDebug()<< error.text();
    }
}

bool stusql::AddUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("INSERT INTO username VALUES ('%1','%2','%3')")
            .arg(info.username)
            .arg(info.password)
            .arg(info.aut);
    qDebug()<<sql.exec(strSql);
}

bool stusql::delUser(QString strUserName)
{
    QSqlQuery sql(m_db);

    return sql.exec(QString("DELETE FROM username WHERE username='%1';").arg(strUserName));

}
