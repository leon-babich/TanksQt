#include "brickwall.h"

BrickWall::BrickWall(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
//    effectShadow = new QGraphicsDropShadowEffect(this);
//    effectShadow->setBlurRadius(5);
//    this->setGraphicsEffect(effectShadow);
}

BrickWall::~BrickWall()
{
}

QRectF BrickWall::boundingRect() const
{
    return QRectF(0, 0, 25, 25);
}

void BrickWall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor sunColor = QColor(255, 255, 255).darker(100);
    QColor brickColor = QColor(250, 90, 70).darker(170);
    qreal sunPart = 0.32;

    QLinearGradient gradient1(0, 0, 25, 8);
    //QRadialGradient gradient1(QPoint(8,3),19);
    gradient1.setColorAt(0.0,sunColor);
    gradient1.setColorAt(sunPart,brickColor);
    painter->setBrush(gradient1);
    painter->drawRect(0, 0, 25, 8);

    QLinearGradient gradient2(0, 8, 12.5, 17);
    //QRadialGradient gradient2(QPoint(8,11),19);
    gradient2.setColorAt(0.0, sunColor);
    gradient2.setColorAt(sunPart, brickColor);
    painter->setBrush(gradient2);
    painter->drawRect(0, 8, 12.5, 8);

    QLinearGradient gradient3(12.5, 8, 25, 17);
    //QRadialGradient gradient3(QPoint(16,11),19);
    gradient3.setColorAt(0.0, sunColor);
    gradient3.setColorAt(sunPart, brickColor);
    painter->setBrush(gradient3);
    painter->drawRect(12.5, 8, 12.5, 8);

    QLinearGradient gradient4(0, 17, 25, 25);
    //QRadialGradient gradient4(QPoint(8,20),19);
    gradient4.setColorAt(0.0, sunColor);
    gradient4.setColorAt(sunPart, brickColor);
    painter->setBrush(gradient4);
    painter->drawRect(0, 17, 25, 8);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
