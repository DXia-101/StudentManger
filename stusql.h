#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
#include <QSqlDatabase>

struct StuInfo{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uiclass;
    quint32 studentid;
    QString phone;
    QString wechat;
};

struct UserInfo{
    QString username;
    QString password;
    QString aut;
};

class stusql : public QObject
{
    Q_OBJECT
public:
    static stusql *ptrstuSql;
    static stusql *getinstance(){
        if(nullptr == ptrstuSql){
            ptrstuSql = new stusql();
        }
        return ptrstuSql;
    }

    explicit stusql(QObject *parent = nullptr);

    void init();

    //查询所有学生数量
    quint32 getStuCnt();
    //查询第几页学生数据,页数从0开始
    QList<StuInfo>  getPageStu(quint32 page,quint32 uiCnt);
    //增加学生
    bool addStu(StuInfo info);
    //删除学生
    bool delStu(int id);
    //清空学生表
    bool clearStuTable();
    //修改学生信息
    bool UpdateStuInfo(StuInfo info);
    //查询所有用户
    QList<UserInfo> getAllUser();
    //查询用户名是否存在
    bool isExit(QString strUser);
    //更新用户信息
    bool UpdateUser(UserInfo info);
    //增加单个用户
    bool AddUser(UserInfo info);
    //删除单个用户
    bool delUser(QString strUserName);
signals:

private:
    QSqlDatabase m_db;
};

#endif // STUSQL_H
