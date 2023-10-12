#include "emblem.h"

Emblem::Emblem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
}

Emblem::~Emblem()
{
}

QRectF Emblem::boundingRect() const
{
    return QRectF(-50,-50,100,100);
}

void Emblem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(":/Image/Images/depositphotos_3667188-stock-illustration-heraldic-eagel.jpg");
    QBitmap bm=pix.createMaskFromColor(QColor(255,255,255));
    QBitmap bm2=pix.createMaskFromColor(QColor(254,254,254));
    pix.setMask(bm);
    pix.setMask(bm2);
    QImage imageEmblem;
    imageEmblem=pix.toImage();
    //imageEmblem.createMaskFromColor(QColor(255,255,255));
    QImage imageEmblemScale=imageEmblem.scaled(imageEmblem.width()/4.5,imageEmblem.height(),Qt::KeepAspectRatio);
    painter->drawImage(-50,-50,imageEmblemScale);
//    painter->setPen(QPen(Qt::black,1));
//    painter->setBrush(QBrush(Qt::black));
//    painter->drawRect(-50,-50,100,100);

//    QPainterPath path;
//    path.moveTo(0,-20);
//    path.lineTo(-15,18);
//    path.lineTo(18,-5);
//    path.lineTo(-18,-5);
//    path.lineTo(15,18);
//    path.lineTo(0,-20);
//    painter->setPen(QPen(Qt::red,1));
//    painter->setBrush(QBrush(Qt::red));
//    painter->drawPath(path);
//    painter->setBrush(QBrush(Qt::darkRed));
//    painter->drawRect(-50,-50,100,100);

//    painter->setBrush(QBrush(Qt::white));
//    painter->drawEllipse(-25,-25,50,50);

//    painter->setPen(QPen(Qt::black,8));
//    QPainterPath path;
//    path.moveTo(0,-20);
//    path.lineTo(-10,-10);
//    path.lineTo(10,10);
//    path.lineTo(0,20);
//    path.moveTo(-20,0);
//    path.lineTo(-10,10);
//    path.lineTo(10,-10);
//    path.lineTo(20,0);
//    painter->drawPath(path);

//    painter->setBrush(QBrush(Qt::darkGreen));
//    painter->drawRect(-50,-50,100,100);

//    painter->setBrush(QBrush(Qt::white));
//    painter->drawEllipse(-27,-27,54,54);

//    painter->setPen(QPen(Qt::black,1));
//    painter->setBrush(QBrush(Qt::black));
//    QPainterPath path;
//    path.moveTo(0,-20);
//    path.lineTo(-2,-18);
//    path.lineTo(-2,18);
//    path.lineTo(2,18);
//    path.lineTo(2,-18);
//    //path.lineTo(0,20);
//    path.moveTo(-10,6);
//    path.lineTo(-10,10);
//    path.lineTo(10,10);
//    path.lineTo(10,6);
//    painter->drawPath(path);
//    painter->drawEllipse(-3,17,6,6);
//    painter->drawRect(-2,6,4,4);
//    painter->drawRect(-10,3,2,5);
//    painter->drawRect(8,3,2,5);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
