#include "tanksymbol.h"

TankSymbol::TankSymbol(QObject *parent) : QObject(parent)
{
}

TankSymbol::~TankSymbol()
{
}

QRectF TankSymbol::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void TankSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor colorSymbol=QColor(200,200,200).darker(150);
    painter->setPen(QPen(colorSymbol,1));
    painter->setBrush(QBrush(colorSymbol));
    painter->drawRect(0,7,7,23);
    painter->drawRect(7,14,16,10);
    painter->drawRect(23,7,7,23);
    painter->drawRect(13,14,4,-12);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
