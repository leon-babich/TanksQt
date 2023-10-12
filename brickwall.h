#ifndef BRICKWALL_H
#define BRICKWALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsEffect>

class BrickWall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BrickWall(QObject *parent = 0);
    ~BrickWall();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QGraphicsDropShadowEffect *effectShadow;
};

#endif // BRICKWALL_H
