#ifndef TANKSYMBOL_H
#define TANKSYMBOL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class TankSymbol : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit TankSymbol(QObject *parent = nullptr);
    ~TankSymbol();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TANKSYMBOL_H
