#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QKeyEvent>
#include"mainwindow2.h"
#include"mydb.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MyDB *getDb() const;
    void setDb(MyDB *value);
    virtual void keyPressEvent(QKeyEvent* e);

private slots:

    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_signupBtn_clicked();

    void on_signInBtn_clicked();

private:
    Ui::MainWindow *ui;
    MainWindow2 *mainW2;
    MyDB *db;
    int page;
};

#endif // MAINWINDOW_H
