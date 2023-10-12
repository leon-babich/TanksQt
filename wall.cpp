#include "wall.h"

Wall::Wall(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
}

Wall::~Wall()
{
}

QRectF Wall::boundingRect() const
{
    return QRectF(-25,-25,50,50);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red,1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(-2.5,-2.5,5,5);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
