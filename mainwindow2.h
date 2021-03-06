#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include"promptwindow.h"
#include"orderwindow.h"
#include"mydb.h"
namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

    Ui::MainWindow2 *getUi() const;
    void setUi(Ui::MainWindow2 *value);
    virtual void keyPressEvent(QKeyEvent* e);
    MyDB *getDb() const;
    void setDb(MyDB *value);
    void setUserNum(QString value);
    void setUserInfo();
    void setAdmin();
    void insertOrderTable(bool b,QString s1,QString s2,QString s3);

    void setUserName(const QString &value);

private slots:

    void on_pushButton_7_clicked();
    void showMagInfo(QString name, QString date);

    void on_pushButton_13_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_choose1_clicked();

    void on_choose2_clicked();

    void on_choose3_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_5_clicked();


    void on_pushButton_15_clicked();

private:
    Ui::MainWindow2 *ui;
    MyDB *db;
    int page;
    QVector<QVector<QString>> searchAns;
    PromptWindow *proWindow;
    OrderWindow *orderWindow;
    QString oldWord;
    QString userNum;
    QString userName;
};

#endif // MAINWINDOW2_H
