#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QGraphicsEffect>
#include <QPropertyAnimation>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "shell.h"
#include "brickwall.h"

enum TypeTank{LIGHT,MEDIUM,HARD};

class Tank : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Tank(QObject *parent = 0);
    ~Tank();
    direction getDirect();
    void countPosition();
    bool checkObstacle();
    bool checkPos();
    bool getIsUnbreak() const;
    bool getIsEnemy() const;
    void activedTimerRecharge();
    TypeTank getTypeArmor() const;
    void setTypeArmor(TypeTank type);
    int getArmor() const;
    void setDamage(int damage);
    void setEnemy(QGraphicsItem *item);
    void clearEnemy();

protected:
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
    void paintTank(QPainter *painter,QColor tankColor);
    void paintEffectUnbreaking(QPainter *painter);

public slots:
    virtual void slotAction()=0;
    void slotRecharge();
    void slotSetBreak();
    void slotChangeStepAnim();

signals:
    void signalShot(Tank *tank);

protected:
    qreal angle;
    direction directTank;
    int xTank;
    int yTank;
    int xRemainder;
    int yRemainder;
    bool isUnbreak;
    bool isEnemy;
    bool isReadyShot;

    QMediaPlayer *playerShot;
    QMediaPlaylist *playlistShot;

    QTimer *timerRecharge;
    QTimer *timerUnbreak;
    QTimer *timerAnimLight;

    QGraphicsDropShadowEffect *effectShadow;
    QGraphicsColorizeEffect *effectUnbreak;
    QPropertyAnimation *animation;

    int countTimeAnim;
    int track;
    int countTrack;
    qreal speed;
    int armor;

    QPoint sunPoint;
    TypeTank typeArmor;
    QGraphicsItem *m_target;
};

#endif // TANK_H
