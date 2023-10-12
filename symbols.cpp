#include "symbols.h"

TankSymbol::TankSymbol(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
}

TankSymbol::~TankSymbol()
{
}

QRectF TankSymbol::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

void TankSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor colorSymbol = QColor(200,200,200).darker(150);

    painter->setPen(QPen(colorSymbol, 1));
    painter->setBrush(QBrush(colorSymbol));

    painter->drawRect(0, 7, 7, 23);
    painter->drawRect(7, 14, 16, 10);
    painter->drawRect(23, 7, 7, 23);
    painter->drawRect(13, 14, 4, -12);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//...........................................................
HeartSymbol::HeartSymbol(QObject *parent) : QObject(parent)
{
}

HeartSymbol::~HeartSymbol()
{
}

QRectF HeartSymbol::boundingRect() const
{
    return QRectF(-15, -15, 30, 30);
}

void HeartSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor colorSymbol = QColor(255, 0, 0).darker(150);

    painter->setPen(QPen(colorSymbol, 2));

    QPainterPath path;
    path.moveTo(0, -5);
    path.cubicTo(-8, -15, -15, 0, 0, 15);
    path.cubicTo(15, 0, 8, -15, 0, -5);
    painter->setBrush(QBrush(colorSymbol));
    painter->drawPath(path);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

