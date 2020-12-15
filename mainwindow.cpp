#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mainW2=new MainWindow2();
    db=new MyDB();
    mainW2->setDb(db);
    ui->setupUi(this);
    page=0;
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    ui->label_3->setParent(this);
    ui->pushButton->setParent(this);
    ui->pushButton_3->setParent(this);
    ui->pushButton->setGeometry(950,0,50,25);
    ui->pushButton_3->setGeometry(905,0,50,25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    page=1;
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_6_clicked()
{
    page=0;
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_signupBtn_clicked()
{
    ui->signupinfo_1->clear();
    ui->signupinfo_2->clear();
    ui->signupinfo_3->clear();
    QString account=ui->signUpAccountLine->text();
    QString password=ui->signUpPassLine->text();
    QString userName;
    bool isAdmin=false;
    bool hasRead=ui->hasReadCheck->isChecked();
    if(account.size()==0){
        ui->signupinfo_1->setText("请输入账户");
    }
    else if(password.size()==0){
        ui->signupinfo_2->setText("请输入密码");
    }
    else if(!hasRead){
        ui->signupinfo_3->setText("请勾选同意各项条款");
    }
    if(account.size()==0||password.size()==0||!hasRead)
        return;
    else{
        if(db->signUp(account,userName,password,isAdmin)){
            qDebug()<<"OK";
            this->close();
            mainW2->setUserNum(account);
            mainW2->setUserName(userName);
            mainW2->setUserInfo();
            if(!isAdmin)
                mainW2->setAdmin();
            mainW2->show();
        }
        else{
            ui->signupinfo_1->setText("登陆失败");
        }
    }
}


void MainWindow::on_signInBtn_clicked()
{
    ui->signininfo_4->clear();
    ui->signininfo_5->clear();
    ui->signininfo_6->clear();
    ui->signininfo_7->clear();
    QString name=ui->signInLine_1->text();
    QString password=ui->signinLine_2->text();
    QString againpass=ui->signInLine3->text();
    QString invite=ui->signInLine4->text();
    QString userName=ui->signInLine4_2->text();
    if(name.size()==0){
        ui->signininfo_4->setText("请输入账户");
        return;
    }else if(userName.size()==0){
        ui->signininfo_8->setText("请输入用户名");
    }
    else if(password.size()==0){
        ui->signininfo_5->setText("请输入密码");
        return;
    }else if(againpass.size()==0){
        ui->signininfo_6->setText("再次输入密码");
        return;
    }else if(ui->radioButton_2->isChecked()&&invite.size()==0){
        ui->signininfo_7->setText("请输入邀请码");
        return;
    }
    if(password!=againpass){
        ui->signininfo_6->setText("请核对密码");
        return;
    }
    if(name.size()==0||password.size()==0||againpass.size()==0||userName.size()==0)
        return;
    if(ui->radioButton->isChecked()){
        bool hasAccount=db->signIn(name,userName,password);
        if(!hasAccount){
            ui->signininfo_4->setText("当前用户已注册");
            return;
        }else{
            ui->signininfo_4->setText("普通用户注册成功");
        }
    }
    else{
        if(invite=="123"){
            bool hasAccount=db->signIn(name,userName,password,"管理员");
            if(!hasAccount){
                ui->signininfo_4->setText("当前用户已注册");
                return;
            }else{
                ui->signininfo_4->setText("管理员注册成功");
            }
        }
        else{
            ui->signininfo_7->setText("邀请码错误，请重试");
            return;
        }
    }
}

MyDB *MainWindow::getDb() const
{
    return db;
}

void MainWindow::setDb(MyDB *value)
{
    db = value;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return){
        if(page==0)
            ui->signupBtn->click();
        else
            ui->signInBtn->click();
        return;
    }
    QWidget::keyPressEvent(e);
}
