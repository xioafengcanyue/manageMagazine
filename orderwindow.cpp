#include "orderwindow.h"
#include "ui_orderwindow.h"

OrderWindow::OrderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    ui->label->setParent(this);
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

void OrderWindow::on_pushButton_2_clicked()
{
    this->close();
    emit hasOver(false,ui->Line1->text(),ui->Line2->text(),ui->Line3->text());
}

void OrderWindow::on_pushButton_clicked()
{
    if(ui->Line1->text().size()==0 ||ui->Line2->text().size()==0||ui->Line3->text().size()==0)
        return;
    this->close();
    emit hasOver(true,ui->Line1->text(),ui->Line2->text(),ui->Line3->text());
}
