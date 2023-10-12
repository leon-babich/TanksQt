#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "tank.h"

class EnemyTank : public Tank
{
    Q_OBJECT
public:
    explicit EnemyTank(TypeTank type, QObject *parent = nullptr);
    ~EnemyTank();
    void returnTank();
    void movingTank();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotAction();

private:
    bool moving;
};

#endif // ENEMYTANK_H
