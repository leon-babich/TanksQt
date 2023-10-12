#ifndef WIDGET_H
#define WIDGET_H

#pragma comment(lib, "User32.lib")

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QPalette>
#include <QShortcut>
#include <QMessageBox>
#include <QVector>
#include <ctime>
#include <QKeyEvent>
#include <QDebug>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "shell.h"
#include "playertank.h"
#include "brickwall.h"
#include "concretewall.h"
#include "enemytank.h"
#include "symbols.h"
#include "button.h"
#include "emblem.h"
#include "effects.h"
#include "windowcounter.h"

enum StateProgram { MENU, GAME };

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);

public slots:
    void slotCreateShot(Tank *tank);
    void slotCreateEnemyTanks();
    void slotDeleteShell(QGraphicsItem* item);
    void slotBlow(QGraphicsItem* it,bool isEnemy,int damage);
    void slotPlayerSignalShot();
    void slotCheckGameOver();
    void slotClickUp();
    void slotClickDown();
    void slotClickEnter();
    void slotClickEsc();
    void slotDeleteRuin();
    void slotDeleteAppearance(bool isEnemy, QPointF placeAppearance);
    void slotChooseButton(Button *button);

signals:
    void signalStartGame();
    void signalGameOver();

private slots:
    void on_butStart_clicked();
    void on_butLoad_clicked();
    void on_butBack_clicked();
    void on_butLevel_1_clicked();
    void on_butLevel_2_clicked();

private:
    Ui::Widget *ui;

    QTimer *timerGame;
    QTimer *timerCheckOver;
    QTimer *timerAppearTanks;

    QGraphicsScene *map;
    QGraphicsScene *description;
    QPalette pal;
    QPalette pal2;

    QList<QGraphicsItem*> listBrickWall;
    QList<QGraphicsItem*> listConcreteWall; 
    QList<Shell*> listShells;
    QList<Tank*> listTanks;
    QList<Ruin*> listRuin;
    QList<Emblem*> listImage;
    QList<Appearance*> listAppearance;
    QVector<TankSymbol*> vectorTankSymbol;
    QVector<Button*> vecButton;
    QVector<HeartSymbol*> vecHeart;

    PlayerTank *playerTank;
    WindowCounter mWindowCounter;

//    QShortcut *keyStart;
//    QShortcut *keyExit;
//    QShortcut *keyShot;
//    QShortcut *keyUp;
//    QShortcut *keyDown;

    QMediaPlayer *playerMenu;
    QMediaPlaylist *playlistMusic;

    int countEnemyTanks;
    int countEnemyTanksLight;
    int countEnemyTanksMedium;
    int countEnemyTanksHard;
    int countTypeEnemyTanks[3];
    int level;
    int timeNextAppearance;
    int mNumberLives;
    bool isEmblem;
    bool mIsFullScreen;

    StateProgram stateProg;

private:
    QPoint countPos();
    void createMap();
    void createDiscription();
    void openMenu();
    void closeMenu();
    void startGame();
    void createSoundAppearance();
    void createSoundShot();
    void createSoundBlow();
    void setResize();
    void loseLife();
    void gameOver();
    void gameVictory();
    void clearAll();
};

#endif // WIDGET_H
