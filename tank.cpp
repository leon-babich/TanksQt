#include "tank.h"

Tank::Tank(QObject *parent) : QObject(parent)
{
    angle = 0;
    directTank = UP;
    isEnemy = false;
    isReadyShot = false;
    setTypeArmor(MEDIUM);
    m_target = nullptr;

    playerShot = new QMediaPlayer(this);
    playlistShot = new QMediaPlaylist(playerShot);

    playerShot->setPlaylist(playlistShot);
    playlistShot->addMedia(QUrl("qrc:/sound/Sounds/TankShot.wav"));
    playlistShot->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playerShot->setVolume(20);

    isReadyShot = true;
    timerRecharge = new QTimer();
    connect(timerRecharge, &QTimer::timeout, this, &Tank::slotRecharge);
    activedTimerRecharge();

    timerUnbreak = new QTimer();
    connect(timerUnbreak, &QTimer::timeout, this, &Tank::slotSetBreak);
    timerUnbreak->start(2000);

    countTimeAnim = 1;
    timerAnimLight = new QTimer();
    connect(timerAnimLight, &QTimer::timeout, this, &Tank::slotChangeStepAnim);
    timerAnimLight->start(100);

    effectShadow = new QGraphicsDropShadowEffect;
    effectShadow->setBlurRadius(5);
    effectShadow->setOffset(4);
    this->setGraphicsEffect(effectShadow);

//    QColor colorUnBreak1=QColor(0,0,0);
//    QColor colorUnBreak2=QColor(255,255,255);

//    effectUnbreak=new QGraphicsColorizeEffect;
//    this->setGraphicsEffect(effectUnbreak);
//    animation=new QPropertyAnimation(effectUnbreak,"color");
//    animation->setStartValue(colorUnBreak1);
//    animation->setEndValue(colorUnBreak2);
//    animation->setDuration(500);
//    animation->setLoopCount(-1);
//    animation->start();

    isUnbreak = true;
    sunPoint = QPoint(0,0);
}

Tank::~Tank()
{

}

QRectF Tank::boundingRect() const
{
    return QRectF(-25,-30,50,50);
}

void Tank::paintTank(QPainter *painter,QColor tankColor)
{
    //корпус
    switch (directTank) {
    case UP:
        sunPoint.setX(-12); sunPoint.setY(-10);
        break;
    case RIGHT:
        sunPoint.setX(-12); sunPoint.setY(10);
        break;
    case DOWN:
        sunPoint.setX(12); sunPoint.setY(10);
        break;
    case LEFT:
        sunPoint.setX(12); sunPoint.setY(-10);
        break;
    default:
        break;
    }
    QRadialGradient gradient(sunPoint,40);
    gradient.setColorAt(0.0,QColor(220,255,220).darker(130));
    gradient.setColorAt(0.5,tankColor);
    painter->setBrush(gradient);
    painter->drawRect(-25,-20,50,40);

    //пушка
    QPoint sun2(0,0);
    switch (directTank) {
    case UP:
        sun2.setX(-4); sun2.setY(-5);
        break;
    case RIGHT:
        sun2.setX(-4); sun2.setY(5);
        break;
    case DOWN:
        sun2.setX(4); sun2.setY(5);
        break;
    case LEFT:
        sun2.setX(4); sun2.setY(-5);
        break;
    default:
        break;
    }
    QRadialGradient gradient2(sun2,25);
    gradient2.setColorAt(0.0,QColor(220,255,220).darker(120));
    gradient2.setColorAt(0.5,tankColor);
    painter->setBrush(gradient2);
    painter->drawRect(-2,-30,4,25);
    painter->drawEllipse(-12.5,-12.5,25,25);
    painter->drawRect(-3,-30,6,6);

    //гусеницы
    painter->setPen(QPen(tankColor,1));
    painter->setBrush(QBrush(tankColor));
    painter->drawRect(-25,-25,10,45);
    painter->drawRect(15,-25,10,45);

    //Траки
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::black));

    if(track==0)
    {
        //левый
        painter->drawEllipse(-25,-17,4,3);
        painter->drawEllipse(-20,-17,4,3);
        painter->drawEllipse(-25,-4,4,3);
        painter->drawEllipse(-20,-4,4,3);
        painter->drawEllipse(-25,9,4,3);
        painter->drawEllipse(-20,9,4,3);
        //правый
        painter->drawEllipse(15,-17,4,3);
        painter->drawEllipse(20,-17,4,3);
        painter->drawEllipse(15,-4,4,3);
        painter->drawEllipse(20,-4,4,3);
        painter->drawEllipse(15,9,4,3);
        painter->drawEllipse(20,9,4,3);
    }
    else if(track==2)
    {
        //левый
        painter->drawEllipse(-25,-25,4,3);
        painter->drawEllipse(-20,-25,4,3);
        painter->drawEllipse(-25,-12,4,3);
        painter->drawEllipse(-20,-12,4,3);
        painter->drawEllipse(-25,1,4,3);
        painter->drawEllipse(-20,1,4,3);
        painter->drawEllipse(-25,14,4,3);
        painter->drawEllipse(-20,14,4,3);
        //правый
        painter->drawEllipse(15,-25,4,3);
        painter->drawEllipse(20,-25,4,3);
        painter->drawEllipse(15,-12,4,3);
        painter->drawEllipse(20,-12,4,3);
        painter->drawEllipse(15,1,4,3);
        painter->drawEllipse(20,1,4,3);
        painter->drawEllipse(15,14,4,3);
        painter->drawEllipse(20,14,4,3);
    }
    else if(track==1)
    {
        //левый
        painter->drawEllipse(-25,-23,4,3);
        painter->drawEllipse(-20,-23,4,3);
        painter->drawEllipse(-25,-10,4,3);
        painter->drawEllipse(-20,-10,4,3);
        painter->drawEllipse(-25,3,4,3);
        painter->drawEllipse(-20,3,4,3);
        painter->drawEllipse(-25,16,4,3);
        painter->drawEllipse(-20,16,4,3);
        //правый
        painter->drawEllipse(15,-23,4,3);
        painter->drawEllipse(20,-23,4,3);
        painter->drawEllipse(15,-10,4,3);
        painter->drawEllipse(20,-10,4,3);
        painter->drawEllipse(15,3,4,3);
        painter->drawEllipse(20,3,4,3);
        painter->drawEllipse(15,16,4,3);
        painter->drawEllipse(20,16,4,3);
    }

    //анимация молнии
//    QColor colorUnBreak1=QColor(0,150,255,60).darker(200);
//    QColor colorUnBreak2=QColor(0,150,255,60).darker(100);

//    this->setGraphicsEffect(effectUnbreak);

//    animation=new QPropertyAnimation(effectUnbreak,"color");
//    animation->setStartValue(colorUnBreak1);
//    animation->setEndValue(colorUnBreak2);
//    animation->setDuration(1000);
//    animation->setLoopCount(-1);
//    animation->start();
}

void Tank::paintEffectUnbreaking(QPainter *painter)
{
    painter->setPen(QPen(Qt::white,0.6));
    QPainterPath path;

    if(countTimeAnim==1)
    {
        path.moveTo(-25,-15);
        path.lineTo(-9,-12);
        path.lineTo(9,-18);
        path.lineTo(25,-15);
        path.moveTo(25,0);
        path.lineTo(9,3);
        path.lineTo(-9,-3);
        path.lineTo(-25,0);
        path.moveTo(-25,15);
        path.lineTo(-9,18);
        path.lineTo(9,12);
        path.lineTo(25,15);

        path.moveTo(-20,-25);
        path.lineTo(-23,-10);
        path.lineTo(-17,5);
        path.lineTo(-20,20);
        path.moveTo(20,20);
        path.lineTo(17,5);
        path.lineTo(23,-10);
        path.lineTo(20,-25);
        path.moveTo(0,-30);
        path.lineTo(3,-10);
        path.lineTo(-3,5);
        path.lineTo(0,20);
    }
    else if(countTimeAnim==2)
    {
        path.moveTo(-25,-5);
        path.lineTo(-9,-18);
        path.lineTo(9,-12);
        path.lineTo(25,-5);
        path.moveTo(25,10);
        path.lineTo(9,-3);
        path.lineTo(-9,3);
        path.lineTo(-25,10);
        path.moveTo(-25,0);
        path.lineTo(-9,12);
        path.lineTo(9,18);
        path.lineTo(25,0);

        path.moveTo(-10,-25);
        path.lineTo(-17,-10);
        path.lineTo(-23,5);
        path.lineTo(-10,20);
        path.moveTo(0,20);
        path.lineTo(23,5);
        path.lineTo(17,-10);
        path.lineTo(0,-25);
        path.moveTo(10,-30);
        path.lineTo(-3,-10);
        path.lineTo(3,5);
        path.lineTo(10,20);
    }

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);

    painter->setPen(Qt::NoPen);
    QColor colorUnBreak1=QColor(0,150,255,128).darker(100);
    QRadialGradient gradient3(sunPoint,45);
    gradient3.setColorAt(0.0,QColor(255,255,255,128));
    gradient3.setColorAt(0.2,colorUnBreak1);
    painter->setBrush(gradient3);
    painter->drawEllipse(-28,-32,55,60);
}

void Tank::slotRecharge()
{
    isReadyShot=true;
    timerRecharge->stop();
}

direction Tank::getDirect()
{
    return directTank;
}

void Tank::countPosition()
{
    xTank=this->x();
    yTank=this->y();
    xRemainder=xTank%STEP;
    yRemainder=yTank%STEP;
}

bool Tank::checkObstacle()
{
    QList<QGraphicsItem*> listItem=scene()->items(QPolygonF()<<mapToScene(0,-20)<<mapToScene(-22,-26)<<mapToScene(22,-26));

    if(listItem.size()>1)
    {
        return true;
    }

    return false;
}

bool Tank::checkPos()
{
   QList<QGraphicsItem*> listItem=scene()->items(QPolygonF()<<mapToScene(-25,-30)<<mapToScene(25,-30)<<mapToScene(25,20)<<mapToScene(-25,20));

   if(listItem.size()>1)
   {
       return false;
   }

   return true;
}

bool Tank::getIsUnbreak() const
{
    return isUnbreak;
}

bool Tank::getIsEnemy() const
{
    return isEnemy;
}

void Tank::activedTimerRecharge()
{
    timerRecharge->start(1000);
}

TypeTank Tank::getTypeArmor() const
{
    return typeArmor;
}

void Tank::setTypeArmor(TypeTank type)
{
    typeArmor=type;

    switch (typeArmor) {
    case LIGHT:
        armor=1;
        speed=1.5;
        break;
    case MEDIUM:
        armor=2;
        speed=1;
        break;
    case HARD:
        armor=3;
        speed=0.7;
        break;
    default:
        break;
    }
}

int Tank::getArmor() const
{
    return armor;
}

void Tank::setDamage(int damage)
{
    armor-=damage;
}

void Tank::slotSetBreak()
{
    if(isUnbreak==true)
    {
        isUnbreak=false;
        timerUnbreak->stop();
    }
    else
    {
        isUnbreak=true;
        timerUnbreak->start(3000);
    }

//    animation->stop();
//    this->setGraphicsEffect(effectShadow);
}

void Tank::slotChangeStepAnim()
{
    if(countTimeAnim==1)
    {
        countTimeAnim=2;
    }
    else
    {
        countTimeAnim=1;
    }
    update(-25,-30,50,50);
}

void Tank::setEnemy(QGraphicsItem *item)
{
    m_target=item;
}

void Tank::clearEnemy()
{
    m_target=nullptr;
}
