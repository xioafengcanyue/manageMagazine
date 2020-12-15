#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QMainWindow>

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void hasOver(bool,QString,QString,QString);
public:
    explicit OrderWindow(QWidget *parent = 0);
    ~OrderWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::OrderWindow *ui;
};

#endif // ORDERWINDOW_H
