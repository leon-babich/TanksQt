#ifndef SHELL_H
#define SHELL_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsEffect>
#include <QDebug>

#include "brickwall.h"

enum direction{LEFT,UP,RIGHT,DOWN};
const int XBOARD=350;
const int YBOARD=350;
const int STEP=25;

class Shell : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Shell(direction direct, const bool isEnemy, int valueDamage, QObject *parent = NULL);
    ~Shell();
    int getDamage() const;

public slots:
    void slotMoveShell();

signals:
    void signalDelete(QGraphicsItem* it);
    void signalBlow(QGraphicsItem* it, bool isEnemy, int valueDamage);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;
    bool isEnemy;
    QGraphicsDropShadowEffect *effectShadow;
    int valueDamage;
};

#endif // SHELL_H
