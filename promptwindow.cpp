#include "promptwindow.h"
#include "ui_promptwindow.h"

PromptWindow::PromptWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PromptWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
}

PromptWindow::~PromptWindow()
{
    delete ui;
}

void PromptWindow::setInfo(bool b, QString m1, QString m2)
{
    if(b){
        ui->ansImg->setPixmap(QPixmap(":/icons/成功.png"));
    }
    else {
        ui->ansImg->setPixmap(QPixmap(":/icons/错误.png"));
    }
    ui->ansLabel->setText(m1);
    ui->infoLabel->setText(m2);
}

void PromptWindow::on_pushButton_clicked()
{
    this->close();
    emit hasConfirm();
}
