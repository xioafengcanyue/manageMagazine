#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include"bookwidget.h"
#include"PageWidget.h"
#include<QDebug>
MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    page=0;
    oldWord="";
    ui->setupUi(this);
    ui->label_2->setParent(this);
    ui->pushButton->setParent(this);
    ui->pushButton_2->setParent(this);
    ui->pushButton_3->setParent(this);
    ui->pushButton_4->setParent(this);
    ui->pushButton_6->setParent(this);
    ui->searchInfoLabel->hide();

    this->setWindowFlags(Qt::FramelessWindowHint);
//    for(int i=0;i<2;i++){
//        ui->verticalLayout->addWidget(new BookWidget());
//    }
    //ui->verticalLayout->addStretch();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<4.;i++){
        ui->tableWidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow2::~MainWindow2()
{
    delete ui;
}

Ui::MainWindow2 *MainWindow2::getUi() const
{
    return ui;
}

void MainWindow2::setUi(Ui::MainWindow2 *value)
{
    ui = value;
}

void MainWindow2::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return){
        if(page==1)
            ui->pushButton_7->click();
        return;
    }
    QWidget::keyPressEvent(e);
}


void MainWindow2::on_pushButton_7_clicked()
{
    QString keyWord=ui->searchLine->text();
    if(oldWord==keyWord)
        return;
    QLayoutItem *child;
    while ((child = ui->verticalLayout->itemAt(0)) != nullptr) {
        ui->verticalLayout->removeItem(child);
        delete child->widget();
        delete child;
        child = nullptr;
    }
    if(keyWord.size()!=0){
        searchAns=db->searchInfo(keyWord);
    }
    if(searchAns.size()!=0)
        ui->searchInfoLabel->hide();
    else
        ui->searchInfoLabel->show();
    //qDebug()<<searchAns.size();
    for(int i=0;i<5;i++){
        if(i==searchAns.size())
            break;
        QString date=searchAns[i][1].append("年").append(searchAns[i][2]).append("卷").append(searchAns[i][3]).append("期");
        BookWidget *bk=new BookWidget(searchAns[i][4],searchAns[i][5],searchAns[i][0],date,QString("馆藏副本：").append(QString::number(1)),QString("可借副本：").append(QString::number(1)));
        connect(bk,&BookWidget::sendMagInfo,this,&MainWindow2::showMagInfo);
        ui->verticalLayout->addWidget(bk);
    }
    ui->verticalLayout->addStretch();
    oldWord=keyWord;

}

void MainWindow2::showMagInfo(QString name, QString date)
{
    ui->stackedWidget->setCurrentIndex(2);
    QVector<QString> info=db->searchMagInfo(name);
    ui->nameInfo->setText(info[0]);
    ui->dateInfo->setText(date);
    ui->CNInfo->setText(info[1]);
    ui->ISSNInfo->setText(info[2]);
    ui->unit->setText(info[4]);
    ui->city->setText(info[5]);
    QVector<QVector<QString>> borInfo=db->searchBronfo(name,date);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(borInfo.size());
    ui->borNum->setText("共"+QString::number(borInfo.size())+"条");
    for(int i=0;i<borInfo.size();i++){
        for(int j=0;j<borInfo[i].size();j++){
            QTableWidgetItem *item=new QTableWidgetItem(borInfo[i][j]);
            ui->tableWidget->setItem(i,j,item);
        }
    }

}

MyDB *MainWindow2::getDb() const
{
    return db;
}

void MainWindow2::setDb(MyDB *value)
{
    db = value;
}

void MainWindow2::setUserNum(QString value)
{
    ui->label_9->setText(value);
    userNum=value;
}

void MainWindow2::setUserInfo()
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_3->clearContents();
    QVector<QVector<QString>> userBro=db->searchUserBro(userNum);
    QVector<QVector<QString>> regBro=db->searchRegister();
    ui->tableWidget_2->setRowCount(userBro.size());
    ui->tableWidget_3->setRowCount(regBro.size());
    for(int i=0;i<userBro.size();i++){
        for(int j=0;j<userBro[i].size();j++){
            QTableWidgetItem *item=new QTableWidgetItem(userBro[i][j]);
            ui->tableWidget_2->setItem(i,j,item);
        }
    }
    for(int i=0;i<regBro.size();i++){
        for(int j=0;j<regBro[i].size();j++){
            QTableWidgetItem *item=new QTableWidgetItem(regBro[i][j]);
            ui->tableWidget_3->setItem(i,j,item);
        }
    }
}

void MainWindow2::setAdmin()
{
    ui->pushButton_4->hide();
    ui->pushButton_6->setGeometry(729,1,111,41);
}

void MainWindow2::on_pushButton_13_clicked()
{
        page=1;
        ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow2::on_pushButton_4_clicked()
{
        page=3;
        ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow2::on_pushButton_2_clicked()
{
    page=6;
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow2::on_pushButton_9_clicked()
{
    QVector<QString> info;
    info.push_back("请输入期刊名称");
    info.push_back("请输入CN刊号");
    info.push_back("请输入ISSN");
    info.push_back("请输入邮发代号");
    info.push_back("请输入出版周期");
    info.push_back("请输入出版地");
    info.push_back("请输入主办单位");
    QVector<QLineEdit*> line;
    QVector<QLabel*> lab;
    QVector<QString> catInfo;
    line.push_back(ui->lineEdit_2);
    line.push_back(ui->lineEdit_3);
    line.push_back(ui->lineEdit_4);
    line.push_back(ui->lineEdit_5);
    line.push_back(ui->lineEdit_6);
    line.push_back(ui->lineEdit_7);
    line.push_back(ui->lineEdit_8);
    line.push_back(ui->lineEdit_9);
    lab.push_back(ui->label_26);
    lab.push_back(ui->label_28);
    lab.push_back(ui->label_30);
    lab.push_back(ui->label_32);
    lab.push_back(ui->label_34);
    lab.push_back(ui->label_36);
    lab.push_back(ui->label_38);
    int k=-1;
    for(int i=0;i<info.size();i++){
        lab[i]->clear();
    }
    for(int i=0;i<line.size();i++){
        if(line[i]->text().size()==0){
            k=i;
            break;
        }
    }
    if(k!=-1&&k!=7){
        lab[k]->setText(info[k]);
        return;
    }
    for(int i=0;i<line.size();i++)
        catInfo.push_back(line[i]->text());
    bool isInsert=db->insertCat(catInfo);
    if(isInsert){
        qDebug()<<"OK";
        for(QLineEdit* li:line)
            li->clear();
        for(QLabel* la:lab)
            la->clear();
    }
}


void MainWindow2::on_pushButton_10_clicked()
{
    QVector<QString> info;
    info.push_back("请输入期刊名称");
    info.push_back("请输入期刊年份");
    info.push_back("请输入期刊卷数");
    info.push_back("请输入期刊期数");
    QVector<QLineEdit*> line;
    QVector<QLabel*> lab;
    QVector<QString> magInfo;
    line.push_back(ui->lineEdit_22);
    line.push_back(ui->lineEdit_23);
    line.push_back(ui->lineEdit_24);
    line.push_back(ui->lineEdit_25);
    lab.push_back(ui->label_76);
    lab.push_back(ui->label_78);
    lab.push_back(ui->label_80);
    lab.push_back(ui->label_82);
    int k=-1;
    for(int i=0;i<info.size();i++){
        lab[i]->clear();
    }
    for(int i=0;i<line.size();i++){
        if(line[i]->text().size()==0){
            k=i;
            break;
        }
    }
    if(k!=-1){
        lab[k]->setText(info[k]);
        return;
    }
    for(int i=0;i<line.size();i++)
        magInfo.push_back(line[i]->text());
    bool isInsert=db->insertMag(magInfo);
    if(isInsert){
        qDebug()<<"OK";
        for(QLineEdit* li:line)
            li->clear();
        for(QLabel* la:lab)
            la->clear();
    }
}

void MainWindow2::on_pushButton_11_clicked()
{
    QVector<QString> info;
    info.push_back("请输入期刊名称");
    info.push_back("请输入期刊年份");
    info.push_back("请输入期刊卷数");
    info.push_back("请输入期刊期数");
    info.push_back("请输入论文题目");
    info.push_back("请输入作者");
    info.push_back("请输入页码");
    info.push_back("请输入关键词1");
    info.push_back("请输入关键词2");
    QVector<QLineEdit*> line;
    QVector<QLabel*> lab;
    QVector<QString> conInfo;
    line.push_back(ui->lineEdit_10);
    line.push_back(ui->lineEdit_11);
    line.push_back(ui->lineEdit_12);
    line.push_back(ui->lineEdit_13);
    line.push_back(ui->lineEdit_14);
    line.push_back(ui->lineEdit_15);
    line.push_back(ui->lineEdit_18);
    line.push_back(ui->lineEdit_19);
    line.push_back(ui->lineEdit_20);
    line.push_back(ui->lineEdit_21);
    line.push_back(ui->lineEdit_16);
    line.push_back(ui->lineEdit_17);
    lab.push_back(ui->label_53);
    lab.push_back(ui->label_55);
    lab.push_back(ui->label_57);
    lab.push_back(ui->label_59);
    lab.push_back(ui->label_61);
    lab.push_back(ui->label_63);
    lab.push_back(ui->label_71);
    lab.push_back(ui->label_81);
    lab.push_back(ui->label_83);
    int k=-1;
    for(int i=0;i<info.size();i++){
        lab[i]->clear();
    }
    for(int i=0;i<line.size();i++){
        if(line[i]->text().size()==0){
            k=i;
            break;
        }
    }
    if(k!=-1&&k<9){
        lab[k]->setText(info[k]);
        return;
    }
    for(int i=0;i<line.size();i++)
        conInfo.push_back(line[i]->text());
    bool isInsert=db->insertCon(conInfo);
    if(isInsert){
        qDebug()<<"OK";
        for(QLineEdit* li:line)
            li->clear();
        for(QLabel* la:lab)
            la->clear();
    }
}

void MainWindow2::on_pushButton_12_clicked()
{
    bool hasBro=db->userBor(userNum,"123",ui->nameInfo->text(),ui->dateInfo->text());
    if(hasBro){
        qDebug()<<"借阅成功";
    }
    else{
        qDebug()<<"已经借阅";

    }

}

void MainWindow2::on_pushButton_6_clicked()
{
    page=0;
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow2::on_pushButton_3_clicked()
{
    page=1;
    ui->stackedWidget->setCurrentIndex(1);
}
