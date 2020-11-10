#include "movelabel.h"
#include<QMouseEvent>
MoveLabel::MoveLabel(QWidget *parent) : QLabel(parent)
{

}

void MoveLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
        m_leftButtonPressed=true;
        m_start=ev->globalPos();
        m_end=parentWidget()->pos();
    }
}

void MoveLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(m_leftButtonPressed)
        parentWidget()->move(ev->globalPos()-m_start+m_end);
}

void MoveLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    m_leftButtonPressed=false;
}
