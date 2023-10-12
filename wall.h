#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Wall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Wall(QObject *parent = 0);
    ~Wall();

public slots:


signals:


protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

};

#endif // WALL_H
