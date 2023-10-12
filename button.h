#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

enum TypeButton{START, LOAD, EXIT};

class Button : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Button(TypeButton typeButton, QObject *parent = nullptr);
    ~Button();
    TypeButton getType() const;
    bool getIsChoose() const;
    void setIsChoose(bool);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

public slots:
    //void slotChoose(Button *button);

signals:
    void sigIsChoose(Button *button);
    void sigClicked();

private:
    TypeButton typeButton;
    bool isChoose;
};


//----------------------------------------------------------------------------------------------------------------

class ButtonLevel : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ButtonLevel(int level, QObject *parent = nullptr);
    ~ButtonLevel();
    bool getIsChoose() const;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotChoose(ButtonLevel *button);

private:
    bool isChoose;
    int mLevel;
};

#endif // BUTTON_H
