#include "effects.h"

Ruin::Ruin(QObject *parent) : QObject(parent)
{
    timerExist=new QTimer();
    connect(timerExist,&QTimer::timeout,this,&Ruin::slotCallEnd);
    timerExist->start(1000);
}

Ruin::~Ruin()
{
}

QRectF Ruin::boundingRect() const
{
    return QRectF(-25,-30,50,50);
}

void Ruin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage imageEmblem(":/Image/Images/Image_ruin.jpg");
    QImage imageEmblemScale=imageEmblem.scaled(imageEmblem.width()/10,imageEmblem.height(),Qt::KeepAspectRatio);
    painter->drawImage(-25,-30,imageEmblemScale);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ruin::slotCallEnd()
{
    emit sigEndExist();
}


//------------------------------------------------------------------------------

Appearance::Appearance(bool isEnemy, QObject *parent) : QObject(parent),isEnemy(isEnemy)
{
    timerExist=new QTimer();
    connect(timerExist,&QTimer::timeout,this,&Appearance::slotCallEnd);
    timerExist->start(1000);

    countTimeAnim=1;
    timerAnimLight=new QTimer();
    connect(timerAnimLight,&QTimer::timeout,this,&Appearance::slotChangeStepAnim);
    timerAnimLight->start(50);
}

Appearance::~Appearance()
{
}

bool Appearance::getTypeEnemy() const
{
    return isEnemy;
}

QRectF Appearance::boundingRect() const
{
    return QRectF(-25,-30,50,50);
}

void Appearance::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::gray,2));
    QPainterPath path;

    if(countTimeAnim==1)
    {
        path.moveTo(-25,-15);
        path.lineTo(-9,-12);
        path.lineTo(9,-18);
        path.lineTo(25,-15);
        path.moveTo(25,0);
        path.lineTo(9,3);
        path.lineTo(-9,-3);
        path.lineTo(-25,0);
        path.moveTo(-25,15);
        path.lineTo(-9,18);
        path.lineTo(9,12);
        path.lineTo(25,15);

        path.moveTo(-20,-25);
        path.lineTo(-23,-10);
        path.lineTo(-17,5);
        path.lineTo(-20,20);
        path.moveTo(20,20);
        path.lineTo(17,5);
        path.lineTo(23,-10);
        path.lineTo(20,-25);
        path.moveTo(0,-30);
        path.lineTo(3,-10);
        path.lineTo(-3,5);
        path.lineTo(0,20);
    }
    else if(countTimeAnim==2)
    {
        path.moveTo(-25,-5);
        path.lineTo(-9,-18);
        path.lineTo(9,-12);
        path.lineTo(25,-5);
        path.moveTo(25,10);
        path.lineTo(9,-3);
        path.lineTo(-9,3);
        path.lineTo(-25,10);
        path.moveTo(-25,0);
        path.lineTo(-9,12);
        path.lineTo(9,18);
        path.lineTo(25,0);

        path.moveTo(-10,-25);
        path.lineTo(-17,-10);
        path.lineTo(-23,5);
        path.lineTo(-10,20);
        path.moveTo(0,20);
        path.lineTo(23,5);
        path.lineTo(17,-10);
        path.lineTo(0,-25);
        path.moveTo(10,-30);
        path.lineTo(-3,-10);
        path.lineTo(3,5);
        path.lineTo(10,20);
    }

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

bool Appearance::checkPos()
{
    QList<QGraphicsItem*> listItem=scene()->items(QPolygonF()<<mapToScene(-25,-30)<<mapToScene(25,-30)<<mapToScene(25,20)<<mapToScene(-25,20));

   if(listItem.size()>1)
   {
       return false;
   }

   return true;
}

void Appearance::slotCallEnd()
{
    emit sigEndExist(isEnemy,this->pos());
}

void Appearance::slotChangeStepAnim()
{
    if(countTimeAnim==1)
    {
        countTimeAnim=2;
    }
    else
    {
        countTimeAnim=1;
    }
    update(-25,-30,50,50);
}
