#include "playertank.h"
//#include <QShortcut>

PlayerTank::PlayerTank(QObject *parent) :
    Tank(parent)
{
    //speed=1;
    track=0;
    countTrack=0;
    timerClick=new QTimer();
    countTimeClick=0;
    isReadyShot=true;
    m_shell=new Shell(DOWN,0,0);
    m_shell=nullptr;
}

PlayerTank::~PlayerTank()
{
}

bool PlayerTank::getIsReadyShot() const
{
    return isReadyShot;
}

void PlayerTank::setIsReadyShot(bool isShot)
{
    isReadyShot=isShot;
}

void PlayerTank::addShell(Shell *shell)
{
    m_shell=shell;
    //listShells.append(shell);
    isReadyShot=false;
}

void PlayerTank::clearShell()
{
    m_shell=nullptr;
    //listShells.clear();
    isReadyShot=true;
}

Shell *PlayerTank::getShell() const
{
    return m_shell;
}

void PlayerTank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor tankColor=QColor(255,200,50).darker(250);

    paintTank(painter,tankColor);

    if(isUnbreak)
    {
        paintEffectUnbreaking(painter);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void PlayerTank::slotAction()
{
    bool tankOnBoarder=false;

    if(((directTank==LEFT)&&(this->x()-(STEP+1)<-XBOARD))||((directTank==RIGHT)&&(this->x()+(STEP+1)>XBOARD))||
            ((directTank==UP)&&(this->y()-(STEP+1)<-XBOARD))||((directTank==DOWN)&&(this->y()+(STEP+1)>XBOARD)))
    {
        tankOnBoarder=true;
    }

    if((GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState(VK_RIGHT)||
            GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))&&!timerClick->isActive())

    {
        timerClick->start(70);
    }

    connect(timerClick,&QTimer::timeout,this,&PlayerTank::slotAdmissionMove);

    if(!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_RIGHT)&&
            !GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))
    {
        timerClick->stop();
        countTimeClick=0;
    }

    //расчет положения на карте
    countPosition();

    //поворот танка
    if((GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))&&
            ((xRemainder==0)&&(yRemainder==0)))
    {
        angle=270;
        directTank=LEFT;
    }
    if((GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))&&
        ((xRemainder==0)&&(yRemainder==0)))
    {
        angle=90;
        directTank=RIGHT;
    }
    if((GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_DOWN))&&
            ((xRemainder==0)&&(yRemainder==0)))
    {
        angle=0;
        directTank=UP;
    }
    if((GetAsyncKeyState(VK_DOWN)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_UP))&&
            ((xRemainder==0)&&(yRemainder==0)))
    {
        angle=180;
        directTank=DOWN;
    }

    setRotation(angle);

    //движение танка
    bool isObstacle=checkObstacle();

    if(((GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))||
            (GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))||
            (GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_DOWN))||
            (GetAsyncKeyState(VK_DOWN)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_UP)))&&
            ((xRemainder==0)||(yRemainder==0))&&!isObstacle&&!tankOnBoarder && helpMove())
    {
        setPos(mapToParent(0,-speed));
    }

    //докат танка до позиционной клетки
    xTank=this->x();
    yTank=this->y();

    if((!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))&&
            (((xRemainder!=0)&&(yRemainder==0))||((xRemainder==0)&&(yRemainder!=0)))&&!isObstacle&&!tankOnBoarder)
    {
        setPos(mapToParent(0,-speed));
    }
    else if((!GetAsyncKeyState(VK_LEFT)&&!GetAsyncKeyState(VK_RIGHT)&&!GetAsyncKeyState(VK_UP)&&!GetAsyncKeyState(VK_DOWN))&&
            (((xRemainder!=0)&&(yRemainder==0))||((xRemainder==0)&&(yRemainder!=0)))&&isObstacle)
    {
        switch (directTank) {
        case LEFT:
            xTank-=(25-xRemainder);
            this->setPos(xTank,yTank);
            break;
        case RIGHT:
            xTank+=(25-xRemainder);
            this->setPos(xTank,yTank);
            break;
        case UP:
            yTank-=(25-yRemainder);
            this->setPos(xTank,yTank);
            break;
        case DOWN:
            yTank+=(25-yRemainder);
            this->setPos(xTank,yTank);
            break;
        default:
            break;
        }
    }
    else if(tankOnBoarder)
    {
        switch (directTank) {
        case LEFT:
            xTank+=(-xRemainder);
            this->setPos(xTank,yTank);
            break;
        case RIGHT:
            xTank-=xRemainder;
            this->setPos(xTank,yTank);
            break;
        case UP:
            yTank+=(-yRemainder);
            this->setPos(xTank,yTank);
            break;
        case DOWN:
            yTank-=yRemainder;
            this->setPos(xTank,yTank);
            break;
        default:
            break;
        }
    }

    if(GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState(VK_RIGHT)||
            GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))

    {
        countTrack++;
        //playerMove->play();
    }
    else
    {
        //playerMove->stop();
    }

    switch (countTrack) {
    case 0:
        track=0;
        update(-25,-30,50,50);
        break;
    case 10:
        track=1;
        update(-25,-30,50,50);
        break;
    case 20:
        track=2;
        update(-25,-30,50,50);
        break;
    case 30:
        track=0;
        update(-25,-30,50,50);
        countTrack=0;
        break;
    default:
        break;
    }

    update(-25,-30,50,50);
}

bool PlayerTank::helpMove()
{
    if((GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState(VK_RIGHT)||
            GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))&&(countTimeClick>150))
    {
        return true;
    }

    return false;
}

void PlayerTank::slotAdmissionMove()
{
    countTimeClick+=70;
}
