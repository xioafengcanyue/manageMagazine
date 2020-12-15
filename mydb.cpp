#include "mydb.h"
#include<QDebug>
#include<QSqlQuery>
#include<QSqlRecord>
#include<algorithm>
#include<QtAlgorithms>
#include<QDateTime>
MyDB::MyDB()
{
    db = QSqlDatabase::addDatabase("QMYSQL");  //连接的MYSQL的数据库驱动
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("magazine");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("root");            //密码
    //测试连接
}


bool MyDB::signUp(QString account, QString& userName, QString password, bool &isAdmin)
{
    db.open();
    bool bisOpen = db.open();          //打开数据库连接
    if(bisOpen)
    {
        QSqlQuery query(db);
        query.exec("select * from user");
        while(query.next()){
            if(account==query.value(0).toString()&&password==query.value(2).toString()){
                userName=query.value(1).toString();
                if(query.value(3)=="管理员")
                    isAdmin=true;
                db.close();
                return true;
            }
        }
        return false;
    }
    return false;
}

bool MyDB::signIn(QString account,QString userName, QString password, QString type)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        query.exec(QString("select * from user where account='%1'").arg(account));
        if(query.size()!=0)
            return false;
        query.exec(QString("insert into user(account, userName,password, type) values('%1','%2','%3','%4')").arg(account,userName,password,type));
        return true;
    }
}

bool MyDB::userBor(QString userNum,QString userName,QString name, QString date)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QStringList searchDate=date.split(QRegExp("年|卷|期"));
        QString year=searchDate[0];
        qDebug()<<searchDate.size();
        QString volume=searchDate[1];
        QString phase=searchDate[2];
        QSqlQuery query(db);
        query.exec(QString("select * from borrow where year='%1' and volume='%2' and phase='%3' and return_date is NULL").arg(year,volume,phase));
        qDebug()<<QString("select * from borrow where year='%1' and volume='%2' and phase='%3' and return_date is NULL").arg(year,volume,phase);
        if(query.size()!=0){
            return false;
        }
        else{
            QString nowTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");
            query.exec(QString("insert into borrow(user_num,user_name,name,year,volume,phase,borrow_date) values('%1','%2','%3','%4','%5','%6','%7')").arg(userNum,userName,name,year,volume,phase,nowTime));
            //qDebug()<<QString("insert into borrow(user_num,user_name,name,year,volume,phase,borrow_date) values('%1','%2','%3','%4','%5','%6','%7')").arg(userNum,userName,name,year,volume,phase,nowTime);

            return true;
        }
    }
}

QVector<QVector<QString>> MyDB::searchInfo(QString keyWord)
{
    QVector<QVector<QString>> ans;
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
       QSqlQuery query(db);
       for(int i=1;i<=7;i++){
           QString sql;
           if(i==7)
               sql=QString("select * from content where name like '%%1%'").arg(keyWord);
           else if(i==6)
               sql=QString("select * from content where title like '%%1%'").arg(keyWord);
           else
               sql=QString("select * from content where key_%1 like '%%2%'").arg(QString::number(i),keyWord);
           query.exec(sql);
           while(query.next()){
               QVector<QString> eachAns;
               for(int i=0;i<query.record().count();i++){
                   eachAns.push_back(query.value(i).toString());
               }
               if(!ans.contains(eachAns))
                   ans.push_back(eachAns);
           }
       }
       return ans;
    }
}

QVector<QString> MyDB::searchMagInfo(QString name)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        query.exec(QString("select * from catalogue where name='%1'").arg(name));
        query.first();
        QVector<QString> info;
        for(int i=0;i<query.record().count();i++){
            info.push_back(query.value(i).toString());
        }
    return info;
    }
}

QVector<QVector<QString>> MyDB::searchBronfo(QString name,QString date)
{
    QVector<QVector<QString>> ans;
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QStringList searchDate=date.split(QRegExp("年|卷|期"));
        QString year=searchDate[0];
        QString volume=searchDate[1];
        QString phase=searchDate[2];
        QSqlQuery query(db);
        query.exec(QString("select user_num,user_name,borrow_date,return_date from borrow where name='%1' and year='%2' and volume='%3' and phase='%4'").arg(name,year,volume,phase));
        //qDebug()<<QString("select user_num,user_name,borrow_date,return_date from borrow where name='%1' and year='%2' and volume='%3' and phase='%4'").arg(name,year,volume,phase);
        while(query.next()){
            QVector<QString> eachAns;
            for(int i=0;i<query.record().count();i++){
                eachAns.push_back(query.value(i).toString());
            }
            ans.push_back(eachAns);
        }
    return ans;
    }
}

QVector<QVector<QString> > MyDB::searchUserBro(QString userName)
{
    QVector<QVector<QString>> ans;
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        query.exec(QString("select * from borrow where user_num='%1'").arg(userName));
        while(query.next()){
            QVector<QString> eachAns;
            for(int i=2;i<query.record().count();i++){
                eachAns.push_back(query.value(i).toString());
            }
            ans.push_back(eachAns);
        }
    return ans;
    }
}

QVector<QVector<QString> > MyDB::searchRegister()
{
    QVector<QVector<QString>> ans;
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        query.exec(QString("select * from orders"));
        while(query.next()){
            QVector<QString> eachAns;
            for(int i=0;i<query.record().count();i++){
                eachAns.push_back(query.value(i).toString());
            }
            ans.push_back(eachAns);
        }
    return ans;
    }
}

bool MyDB::insertCat(QVector<QString> catInfo)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        QString sql="insert into catalogue(name,cn_issn,issn,postal_code,bimonthly,place,publisher,note) values('%1','%2','%3','%4','%5','%6','%7','%8')";
        for(int i=0;i<catInfo.size();i++)
            sql=sql.arg(catInfo[i]);

        return query.exec(sql);
    }
    return false;
}

bool MyDB::insertMag(QVector<QString> magInfo)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        QString sql="insert into register(name,year,volume,phase) values('%1','%2','%3','%4')";
        for(int i=0;i<magInfo.size();i++)
            sql=sql.arg(magInfo[i]);
        return query.exec(sql);
    }
    return false;
}

bool MyDB::insertCon(QVector<QString> ConInfo)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        QString sql="insert into content(name,year,volume,phase,title,author,key_1,key_2,key_3,key_4,key_5,page) values('%1','%2','%3','%4','%5','%6','%8','%9','%10','%11','%12','%7')";
        for(int i=0;i<ConInfo.size();i++)
            sql=sql.arg(ConInfo[i]);

        qDebug()<<sql;
        return query.exec(sql);
    }
    return false;
}

bool MyDB::insertOrder(QString s1, QString s2, QString s3)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        QString sql="insert into orders(postal_code,name,order_date,is_order) values('%1','%2','%3','否')";
        sql=sql.arg(s1,s2,s3);

        qDebug()<<sql;
        return query.exec(sql);
    }
    return false;
}

bool MyDB::returnBook(QVector<QString> returnInfo)
{
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy-MM-dd");
        QSqlQuery query(db);
        //QString sql="select COUNT(*) from borrow where user_num='%1' and user_name='%2' and name='%3' and year='%4' and volume='%5' and phase='%6' and borrow_date='%7'";
        //QString sql="insert into orders(postal_code,name,order_date) values('%1','%2','%3')";
        QString sql="update borrow set return_date='%8' where user_num='%1' and user_name='%2' and name='%3' and year='%4' and volume='%5' and phase='%6' and borrow_date='%7'";
        returnInfo.push_back(current_date);
        for(int i=0;i<returnInfo.size();i++){
            sql=sql.arg(returnInfo[i]);
        }
        qDebug()<<sql;
        return query.exec(sql);
    }
    return false;
}
bool MyDB::confirmOrder(QVector<QString> returnInfo){
    db.open();
    bool bisOpen=db.open();
    if(bisOpen){
        QSqlQuery query(db);
        //QString sql="select COUNT(*) from borrow where user_num='%1' and user_name='%2' and name='%3' and year='%4' and volume='%5' and phase='%6' and borrow_date='%7'";
        //QString sql="insert into orders(postal_code,name,order_date) values('%1','%2','%3')";
        QString sql="update orders set is_order='是' where postal_code='%1' and name='%2' and order_date='%3'";
        for(int i=0;i<returnInfo.size();i++){
            sql=sql.arg(returnInfo[i]);
        }
        qDebug()<<sql;
        return query.exec(sql);
    }
    return false;
}
