#include "bookwidget.h"
#include "ui_bookwidget.h"

BookWidget::BookWidget(QString title, QString author, QString name, QString date, QString all, QString leaft, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWidget)
{
    ui->setupUi(this);
    setInfo(title,author,name,date,all,leaft);
}

void BookWidget::setInfo(QString title, QString author,QString name, QString date, QString all, QString leaft)
{
    ui->title->setText(title);
    ui->author->setText(author);
    ui->name->setText(name);
    ui->date->setText(date);
    ui->all->setText(all);
    ui->leaft->setText(leaft);
}

BookWidget::~BookWidget()
{
    delete ui;
}

void BookWidget::on_title_clicked()
{
    emit sendMagInfo(ui->name->text(),ui->date->text());
}
