#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>

namespace Ui {
class BookWidget;
}

class BookWidget : public QWidget
{
    Q_OBJECT
signals:
    void sendMagInfo(QString name,QString date);
public:
    explicit BookWidget(QString title,QString author,QString name,QString date,QString all,QString leaft,QWidget *parent = 0);
    void setInfo(QString title,QString author,QString name,QString date,QString all,QString leaft);
    ~BookWidget();

private slots:
    void on_title_clicked();

private:
    Ui::BookWidget *ui;
};

#endif // BOOKWIDGET_H
