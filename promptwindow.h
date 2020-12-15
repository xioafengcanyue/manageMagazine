#ifndef PROMPTWINDOW_H
#define PROMPTWINDOW_H

#include <QMainWindow>

namespace Ui {
class PromptWindow;
}

class PromptWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void hasConfirm();
public:
    explicit PromptWindow(QWidget *parent = 0);
    ~PromptWindow();
    void setInfo(bool b,QString m1,QString m2);

private slots:
    void on_pushButton_clicked();
private:
    Ui::PromptWindow *ui;
};

#endif // PROMPTWINDOW_H
