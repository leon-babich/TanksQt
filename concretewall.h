#ifndef CONCRETEWALL_H
#define CONCRETEWALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsEffect>

class ConcreteWall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ConcreteWall(QObject *parent = 0);
    ~ConcreteWall();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QGraphicsDropShadowEffect *effectShadow;
};

#endif // CONCRETEWALL_H
