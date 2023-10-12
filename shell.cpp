#include "shell.h"

Shell::Shell(direction direct, const bool isEnemy, int valueDamage, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->isEnemy = isEnemy;

    switch (direct) {
    case LEFT:
        angle = 270;
        break;
    case UP:
        angle = 0;
        break;
    case RIGHT:
        angle = 90;
        break;
    case DOWN:
        angle = 180;
        break;
    default:
        break;
    }

    this->valueDamage=valueDamage;
    setRotation(angle);

    effectShadow = new QGraphicsDropShadowEffect;
    effectShadow->setBlurRadius(5);
    effectShadow->setOffset(15);
    this->setGraphicsEffect(effectShadow);
}

Shell::~Shell()
{
}

int Shell::getDamage() const
{
    return valueDamage;
}

QRectF Shell::boundingRect() const
{
    return QRectF(-3, -3, 6, 6);
}

void Shell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(-2.5, -2.5, 5, 5);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Shell::slotMoveShell()
{
    const qreal SPEED = 2.4;

    setPos(mapToParent(0, -SPEED));

    QList<QGraphicsItem *> listFindItem;
    listFindItem = scene()->items(QPolygonF()<<mapToScene(0,0)<<mapToScene(-10,-2)<<mapToScene(10,-2));

    if(listFindItem.size() > 1) {
        foreach (QGraphicsItem* it, listFindItem) {
            if(it == this) {
                continue;
            }

            emit signalBlow(it, isEnemy, valueDamage);
        }

        emit signalDelete(this);
    }

    if(this->x() < -XBOARD || this->x() > XBOARD || this->y() < -YBOARD || this->y() > YBOARD) {
        emit signalDelete(this);
    }
}
