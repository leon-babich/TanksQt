#ifndef EMBLEM_H
#define EMBLEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QBitmap>

class Emblem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Emblem(QObject *parent = nullptr);
    ~Emblem();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EMBLEM_H
