#ifndef QANIMATIONSTACKEDWIDGET_H
#define QANIMATIONSTACKEDWIDGET_H

#include <QWidget>
#include<QStackedWidget>
#include<QPropertyAnimation>
class QAnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit QAnimationStackedWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    //设置动画持续的间隔
    void setDuration(int );

    //~QAnimationStackedWidget();

signals:

public slots:
    //属性动画值改变的槽
    void valueChanged_slot(QVariant );
    //动画切换完成
    void animationFinished();
    //前一页
    void next();
    //下一页
    void forward();

private:
    void paintPrevious(QPainter &, int);

    void paintNext(QPainter &, int);

private:
    QPropertyAnimation *animation; //动画框架
    int duration;                   //动画的持续时间
    bool isAnimation;               //是否正在动画
    QVariant       currentValue;    //被Animation动画改变的值
    int         widgetCount;        //保存当前StackWidget里面的子成员数
    int         nextIndex;          //下一个要切换的索引
};

#endif // QANIMATIONSTACKEDWIDGET_H
