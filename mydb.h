#ifndef MYDB_H
#define MYDB_H
#include<QtSql/QSqlDatabase>
#include<QVector>
class MyDB
{
public:
    MyDB();
    bool signUp(QString account,QString password);
    bool signIn(QString account,QString password,QString type="普通用户");
    bool userBor(QString userNum, QString userName, QString name, QString date);
    QVector<QVector<QString>> searchInfo(QString keyWord);
    QVector<QString> searchMagInfo(QString name);
    QVector<QVector<QString>> searchBronfo(QString name, QString date);
    QVector<QVector<QString>> searchUserBro(QString userName);
    QVector<QVector<QString>> searchRegister();
    bool insertCat(QVector<QString> catInfo);
    bool insertMag(QVector<QString> magInfo);
    bool insertCon(QVector<QString> ConInfo);
private:
    QSqlDatabase db;
};

#endif // MYDB_H
