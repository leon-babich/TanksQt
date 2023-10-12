#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

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



//Класс символа "сердца".............................................................

class HeartSymbol : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HeartSymbol(QObject *parent = nullptr);
    ~HeartSymbol();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SYMBOLS_H
