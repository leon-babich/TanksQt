#include "button.h"

Button::Button(TypeButton type, QObject *parent):
    QObject(parent), QGraphicsItem()
{
    this->typeButton=type;
    isChoose=false;
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

Button::~Button()
{
}

QRectF Button::boundingRect() const
{
    return QRectF(0,0,200,50);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor colorButton=QColor(0,0,255).darker(120);
    QColor sunColor=QColor(255,255,255).darker(120);

    QRadialGradient gradient(QPoint(100,12),250);
    gradient.setColorAt(0.0,colorButton);
    gradient.setColorAt(0.7,sunColor);
    painter->setBrush(gradient);
    painter->drawRect(0,0,200,50);

    if(isChoose)
    {
        painter->setPen(QPen(Qt::red,3));
        painter->drawLine(3,3,200,3);
        painter->drawLine(200,3,200,50);
        painter->drawLine(200,50,3,50);
        painter->drawLine(3,50,3,3);
    }

    QPointF pointBegin;
    QString title;

    switch (typeButton) {
    case START:
        pointBegin=QPointF(71,20);
        title="Начать";
        break;
    case LOAD:
        pointBegin=QPointF(71,20);
        title="Загрузка";
        break;
    case EXIT:
        pointBegin=QPointF(81,20);
        title="Выход";
        break;
    default:
        break;
    }

    painter->setPen(QPen(Qt::white,2));
    QFont font("",15);
    painter->setFont(font);
    painter->drawText(pointBegin,title);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit sigIsChoose(this);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //setIsChoose(false);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigClicked();
}

//void Button::slotChoose(Button *button)
//{
//    if(button==this)
//    {
//        if(!isChoose)
//        {
//            isChoose=true;
//        }
//        else
//        {
//            isChoose=false;
//        }
//    }

//    update(0,0,200,50);
//}

TypeButton Button::getType() const
{
    return typeButton;
}

bool Button::getIsChoose() const
{
    return isChoose;
}

void Button::setIsChoose(bool isChoose)
{
    this->isChoose=isChoose;
    update(0,0,200,50);
}


//----------------------------------------------------------------

ButtonLevel::ButtonLevel(int level, QObject *parent):
    QObject(parent), QGraphicsItem()
{
    isChoose=false;
    mLevel=level;
}

ButtonLevel::~ButtonLevel()
{
}

QRectF ButtonLevel::boundingRect() const
{
    return QRectF(0,0,200,50);
}

void ButtonLevel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor colorButton=QColor(0,0,255).darker(120);
    QColor sunColor=QColor(255,255,255).darker(120);

    QRadialGradient gradient(QPoint(100,12),250);
    gradient.setColorAt(0.0,colorButton);
    gradient.setColorAt(0.7,sunColor);
    painter->setBrush(gradient);
    painter->drawRect(0,0,200,50);

    if(isChoose)
    {
        painter->setPen(QPen(Qt::red,3));
        painter->drawLine(3,3,200,3);
        painter->drawLine(200,3,200,50);
        painter->drawLine(200,50,3,50);
        painter->drawLine(3,50,3,3);
    }

    QPointF pointBegin;
    QString title;
    QString title1;
    QString title2;

    pointBegin=QPointF(71,20);
    title1="Уровень";
    title2.setNum(mLevel);
    title=title1+title2;

    painter->setPen(QPen(Qt::white,2));
    QFont font("",15);
    painter->setFont(font);
    painter->drawText(pointBegin,title);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void ButtonLevel::slotChoose(ButtonLevel *button)
{
    if(button==this)
    {
        if(!isChoose)
        {
            isChoose=true;
        }
        else
        {
            isChoose=false;
        }
    }

    update(0,0,200,25);
}

bool ButtonLevel::getIsChoose() const
{
    return isChoose;
}
