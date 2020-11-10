#ifndef MOVELABEL_H
#define MOVELABEL_H

#include<QLabel>
#include<QPoint>
class MoveLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MoveLabel(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
private:
    QPoint m_start;
    QPoint m_end;
    bool m_leftButtonPressed;
signals:

public slots:
};

#endif // MOVELABEL_H
