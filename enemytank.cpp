#include "enemytank.h"

EnemyTank::EnemyTank(TypeTank type, QObject *parent) : Tank(parent)
{
    moving=false;
    //speed=1;
    isEnemy=true;
    track=0;
    countTrack=0;
    setTypeArmor(type);
}

EnemyTank::~EnemyTank()
{
}

void EnemyTank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QColor tankColor=QColor(0,255,0).darker(400);
    QColor tankColor;

    switch (typeArmor) {
    case LIGHT:
        tankColor=QColor(255,100,100).darker(300);
        break;
    case MEDIUM:
        tankColor=QColor(0,255,0).darker(400);
        break;
    case HARD:
        tankColor=QColor(255,255,255).darker(300);
        break;
    default:
        break;
    }

    paintTank(painter,tankColor);

    if(isUnbreak)
    {
        paintEffectUnbreaking(painter);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void EnemyTank::slotAction()
{
    int randAction=2;

    if(!moving)
    {
        randAction=qrand()%25;
    }

    QList<QGraphicsItem*> listItem=scene()->items(QPolygonF()<<mapToScene(-20,-200)<<mapToScene(20,-200)<<mapToScene(20,20)<<mapToScene(-20,20));

    foreach (QGraphicsItem *item, listItem) {
        if(item==m_target) {
            randAction=5;
        }
    }

    switch (randAction) {
    case 1:
        returnTank();
        break;
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        movingTank();
        break;
    case 5:
        if(isReadyShot)
        {
            playerShot->play();
            emit signalShot(this);
            isReadyShot=false;
            activedTimerRecharge();
        }
        break;
    default:
        break;
    }
}

void EnemyTank::returnTank()
{
    int randAngle=qrand()%6+1;

    switch (randAngle) {
    case 1:
        angle=270;
        directTank=LEFT;
        break;
    case 2:
        angle=90;
        directTank=RIGHT;
        break;
    case 3:
        angle=0;
        directTank=UP;
        break;
    case 4:
    case 5:
    case 6:
        angle=180;
        directTank=DOWN;
        break;
    default:
        break;
    }

    setRotation(angle);
}

void EnemyTank::movingTank()
{
    bool tankOnBorder=false;

    //определение условия выхода танка за границы карты
    if(((directTank==LEFT)&&(this->x()-(STEP+1)<-XBOARD))||((directTank==RIGHT)&&(this->x()+(STEP+1)>XBOARD))||
            ((directTank==UP)&&(this->y()-(STEP+1)<-XBOARD))||((directTank==DOWN)&&(this->y()+(STEP+1)>XBOARD)))
    {
        tankOnBorder=true;
    }

    bool isObstacle=checkObstacle();
    countPosition();

    if(((xRemainder==0)||(yRemainder==0)) && !isObstacle && !tankOnBorder)
    {
        setPos(mapToParent(0,-speed));
        moving=true;
        countTrack++;
    }

    countPosition();
    if((xRemainder==0)&&(yRemainder==0))
    {
        moving=false;
    }

    if(isObstacle && moving)
    {
        switch (directTank) {
        case LEFT:
            angle=90;
            directTank=RIGHT;
            break;
        case RIGHT:
            angle=270;
            directTank=LEFT;
            break;
        case UP:
            angle=180;
            directTank=DOWN;
            break;
        case DOWN:
            angle=0;
            directTank=UP;
            break;
        default:
            break;
        }

        setRotation(angle);
    }

    switch (countTrack) {
    case 0:
        track=0;
        break;
    case 10:
        track=1;
        break;
    case 20:
        track=2;
        break;
    case 30:
        track=0;
        countTrack=0;
        break;
    default:
        break;
    }

    update(-25,-30,50,50);
}

