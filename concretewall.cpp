#include "concretewall.h"

ConcreteWall::ConcreteWall(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
//    effectShadow = new QGraphicsDropShadowEffect;
//    effectShadow->setBlurRadius(5);
//    this->setGraphicsEffect(effectShadow);
}

ConcreteWall::~ConcreteWall()
{
}

QRectF ConcreteWall::boundingRect() const
{
    return QRectF(0, 0, 25, 25);
}

void ConcreteWall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRadialGradient gradient(QPoint(8, 8), 19);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(0.5, Qt::gray);
    gradient.setColorAt(1.0, QColor(255, 255, 255).darker(200));
    painter->setBrush(gradient);
    painter->drawRect(0, 0, 25, 25);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
