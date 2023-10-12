#ifndef EFFECTS_H
#define EFFECTS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>

//Еффект руин.............................................................

class Ruin : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Ruin(QObject *parent = nullptr);
    ~Ruin();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotCallEnd();

signals:
    void sigEndExist();

private:
    QTimer *timerExist;
};


//Еффект появления танка.............................................................

class Appearance : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Appearance(bool isEnemy, QObject *parent = nullptr);
    ~Appearance();
    bool getTypeEnemy() const;
    bool checkPos();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotCallEnd();
    void slotChangeStepAnim();

signals:
    void sigEndExist(bool isEnemy, QPointF placeAppearance);

private:
    QTimer *timerExist;
    QTimer *timerAnimLight;
    int countTimeAnim;
    bool isEnemy;
};

#endif // EFFECTS_H
