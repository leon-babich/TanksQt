#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Tanks");
    QPixmap pix(":/Image/Images/T64_5.gif");
//    QBitmap bm = pix.createMaskFromColor(QColor(255, 255, 255));
//    pix.setMask(bm);
    this->setWindowIcon(pix);

    this->setMinimumSize(500, 400);
//    ui->groupBoxWindow->setFixedSize(500, 400);
//    ui->groupBoxWindow->setAlignment(Qt::AlignLeft);
//    ui->graphicsView_2->setAlignment(Qt::AlignLeft);
//    this->setFixedSize(1000, 800);
    //this->showFullScreen();

//    QSizePolicy policy(this->sizePolicy());
//    policy.setHeightForWidth(true);
//    this->setSizePolicy(policy);

    ui->graphicsView->resize(W1, H_Window);
    ui->graphicsView_2->resize(W2, H_Window);
    mWindowCounter.setSizeWindow(W1, H_Window, W2);
    //ui->graphicsView_2->setFixedSize(100,700);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    m_widthView_1 = ui->graphicsView->size().width();
//    m_heightView_1 = ui->graphicsView->size().height();
//    m_widthView_2 = ui->graphicsView_2->size().width();
//    m_heightView_2 = ui->graphicsView_2->size().height();

    int widthBut = 200;
    int heightBut = 30;
    ui->butStart->setFixedSize(widthBut, heightBut);
    ui->butLoad->setFixedSize(widthBut, heightBut);
    ui->butExit->setFixedSize(widthBut, heightBut);

    int widthBut_2 = 100;
    int heightBut_2 = 100;
    ui->butLevel_1->setFixedSize(widthBut_2, heightBut_2);
    ui->butLevel_2->setFixedSize(widthBut_2, heightBut_2);
    ui->butLevel_3->setFixedSize(widthBut_2, heightBut_2);
    ui->butLevel_4->setFixedSize(widthBut_2, heightBut_2);
    ui->butLevel_5->setFixedSize(widthBut_2, heightBut_2);
    ui->butLevel_6->setFixedSize(widthBut_2, heightBut_2);

    ui->butLevel_3->setEnabled(false);
    ui->butLevel_4->setEnabled(false);
    ui->butLevel_5->setEnabled(false);
    ui->butLevel_6->setEnabled(false);

    map = new QGraphicsScene();
    ui->graphicsView->setScene(map);
    map->setSceneRect(-300, -300, 600, 600);

    description = new QGraphicsScene();
    ui->graphicsView_2->setScene(description);
    description->setSceneRect(-40, -300, 80, 600);

    timerGame = new QTimer();

    playerMenu = new QMediaPlayer(this);
    playlistMusic = new QMediaPlaylist(playerMenu);
    playerMenu->setPlaylist(playlistMusic);
    playlistMusic->addMedia(QUrl("qrc:/sound/Sounds/alizje-thunderpiano.mp3"));
    playlistMusic->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    Button *buttonStart = new Button(START);
    vecButton.append(buttonStart);
    Button *buttonLoad = new Button(LOAD);
    vecButton.append(buttonLoad);
    Button *buttonExit = new Button(EXIT);
    vecButton.append(buttonExit);

    level = 1;
    isEmblem = false;
    mIsFullScreen = false;
    mNumberLives = 1;

    //closeMenu();
    //ui->graphicsView_2->hide();
    openMenu();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    setResize();
    Q_UNUSED(event);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape) {
        slotClickEsc();
    }
    if(e->key() == Qt::Key_Return) {
        if(mIsFullScreen) {
            this->showNormal();
            mIsFullScreen = false;
        }
        else {
            this->showFullScreen();
            mIsFullScreen = true;
        }

        setResize();
    }
    if(e->key() == Qt::Key_Up) {
        slotClickUp();
    }
    if(e->key() == Qt::Key_Down) {
        slotClickDown();
    }
    if(e->key() == Qt::Key_D) {
        slotPlayerSignalShot();
    }
    if(e->key() == Qt::Key_Q) {
        loseLife();
    }
}

void Widget::slotCreateShot(Tank *tank)
{
    direction dirTank = tank->getDirect();
    int valueDamage = (tank->getArmor() == LIGHT ? 1 : 2);

    Shell *shell = new Shell(dirTank, tank->getIsEnemy(), valueDamage);
    listShells.append(shell);

    if(tank == playerTank) {
        playerTank->addShell(shell);
    }

    qreal xTank = tank->x();
    qreal yTank = tank->y();

    QPointF point;

    switch (dirTank) {
    case LEFT:
        point.setX(xTank - 40);
        point.setY(yTank);
        break;
    case UP:
        point.setX(xTank);
        point.setY(yTank - 40);
        break;
    case RIGHT:
        point.setX(xTank + 40);
        point.setY(yTank);
        break;
    case DOWN:
        point.setX(xTank);
        point.setY(yTank + 40);
        break;
    default:
        break;
    }

    map->addItem(shell);
    shell->setPos(point);

    connect(timerGame, &QTimer::timeout, shell, &Shell::slotMoveShell);
    connect(shell, &Shell::signalBlow, this, &Widget::slotBlow);
    connect(shell, &Shell::signalDelete, this, &Widget::slotDeleteShell);
}

void Widget::slotCreateEnemyTanks()
{
    if((countEnemyTanks <= 0) || (listTanks.size() > 8)) {
        return;
    }

    Appearance *appearance = new Appearance(true);
    listAppearance.append(appearance);
    map->addItem(appearance);
    appearance->setPos(countPos());
    connect(appearance, &Appearance::sigEndExist, this, &Widget::slotDeleteAppearance);
    //createSoundAppearance();

    while(!appearance->checkPos())
    {
        appearance->setPos(countPos());
    }

    if(listTanks.size()<5)
    {
        timeNextAppearance = 5000;
    }
    else if(listTanks.size() < 8)
    {
        timeNextAppearance = 7000;
    }
    else
    {
        timeNextAppearance = 10000;
    }

    timerAppearTanks->start(timeNextAppearance);
}

void Widget::slotDeleteShell(QGraphicsItem* item)
{
    if(item == playerTank->getShell()) {
        playerTank->clearShell();
    }

    foreach(Shell* shell, listShells) {
        if(shell == item) {
            map->removeItem(shell);
            listShells.removeOne(shell);
            delete shell;
        }
    }
}

void Widget::slotBlow(QGraphicsItem* it, bool isEnemy, int damage)
{
    foreach (QGraphicsItem* wall, listBrickWall) {
        if(it == wall) {
            map->removeItem(it);
            listBrickWall.removeOne(wall);
            delete it;
            return;
        }
    }

    foreach (Tank* tank, listTanks) {
        if((it == tank) && (!isEnemy || (isEnemy && !tank->getIsEnemy())) && !tank->getIsUnbreak()) {
            createSoundBlow();

            tank->setDamage(damage);

            if(tank->getArmor() <= 0) {
                if(tank->getIsEnemy()) {
                    QPointF placeTank = tank->pos();

                    map->removeItem(it);
                    listTanks.removeOne(tank);
                    delete it;

                    if(listTanks.empty()) {
                        gameVictory();
                    }

                    Ruin *ruin = new Ruin();
                    listRuin.append(ruin);
                    map->addItem(ruin);
                    ruin->setPos(placeTank);
                    connect(ruin, &Ruin::sigEndExist, this, &Widget::slotDeleteRuin);

                    TankSymbol *symbol = vectorTankSymbol.back();
                    description->removeItem(symbol);
                    vectorTankSymbol.pop_back();
                    delete symbol;
                }
                else {
                    loseLife();
                }
            }

            return;
        }
    }

    foreach (Shell* shell, listShells) {
        if(it == shell) {
            emit shell->signalDelete(shell);
            return;
        }
    }

    foreach (Emblem* img, listImage) {
        if(it == img) {
            map->removeItem(img);
            listImage.removeOne(img);
            delete img;
            isEmblem = false;
            gameOver();
            return;
        }
    }
}

void Widget::slotPlayerSignalShot()
{
    if(playerTank->getIsReadyShot()) {
        createSoundShot();
        emit playerTank->signalShot(playerTank);
    }
}

void Widget::slotCheckGameOver()
{
    bool isVictory = true;
    bool isLost = true;

    foreach (Tank* tank, listTanks) {
        if(tank->getIsEnemy()) {
            isVictory = false;
        }

        if(!tank->getIsEnemy()) {
            isLost = false;
        }
    }

//    if((isVictory && (countEnemyTanks == 0)) || isLost || listImage.isEmpty()) {
//        emit signalGameOver();
//    }
}

void Widget::gameOver()
{
    timerGame->stop();
    timerAppearTanks->stop();
    timerCheckOver->stop();

    if(vecHeart.empty() || !isEmblem) {
        QMessageBox::warning(this, "Game over", "Вы проиграли.\nНажмите 'OK' для выхода из игры.");
        clearAll();
        openMenu();
    }
}

void Widget::gameVictory()
{
    timerGame->stop();
    timerAppearTanks->stop();
    timerCheckOver->stop();

    int finishLevel = 2;

    if(level < finishLevel) {
        QMessageBox::about(this, "Game over", "Поздравляю. Вы выграли.\n"
                                            "Нажмите 'OK' для перехода к следующему уровню.");
        level++;
        startGame();
    }
    else {
        QMessageBox::about(this, "Game over", "VICTORY\n\n\nНажмите 'OK' для выхода из игры.");
        openMenu();
    }

//    if((level < 2) && continueGame) {
//        level++;
//        startGame();
//    }
//    else if(continueGame) {
//         QMessageBox::about(this, "Game over", "VICTORY\n\n\nНажмите 'OK' для выхода из игры.");
//    }
//    else {
//        openMenu();
//    }
}

void Widget::slotClickUp()
{
    int n = 0;

    foreach (Button *button, vecButton) {
        if(button->getIsChoose()) {
            break;
        }
        n++;
    }

    if(vecButton[n] != vecButton.first()) {
        slotChooseButton(vecButton[n-1]);
    }
}

void Widget::slotClickDown()
{
    int n = 0;

    foreach (Button *button, vecButton) {
        if(button->getIsChoose()) {
            break;
        }

        n++;
    }

    if(vecButton[n] != vecButton.back()) {
        slotChooseButton(vecButton[n + 1]);
    }
}

void Widget::slotClickEnter()
{
    Button *chooseButton;

    foreach (Button *button, vecButton) {
        if(button->getIsChoose()) {
            chooseButton = button;
        }
    }
    if(stateProg == MENU) {
        switch (chooseButton->getType()) {
        case START:
            startGame();
            break;
        case LOAD:
            break;
        case EXIT:
            exit(0);
        default:
            break;
        }
    }
}

void Widget::slotClickEsc()
{
    if(stateProg == MENU) {
        exit(0);
    }
    else if(stateProg == GAME) {
        clearAll();
        openMenu();
    }
}

void Widget::slotDeleteRuin()
{
    Ruin *ruin = listRuin.first();
    listRuin.removeOne(ruin);
    map->removeItem(ruin);
    delete ruin;
}

void Widget::slotDeleteAppearance(bool isEnemy, QPointF placeAppearance)
{
    Appearance *appearance = listAppearance.first();
    listAppearance.removeOne(appearance);
    map->removeItem(appearance);
    delete appearance;

    if(isEnemy) {
        int randomType = 1;

        if(countEnemyTanks <= 7) {
            randomType = qrand() % 3;

            while (countTypeEnemyTanks[randomType] == 0) {
                randomType = qrand() % 3;
            }
        }

        EnemyTank* enemyTank = new EnemyTank((TypeTank)randomType);
        listTanks.append(enemyTank);
        map->addItem(enemyTank);
        countEnemyTanks--;
        countTypeEnemyTanks[randomType]--;
        enemyTank->setPos(placeAppearance);
        enemyTank->setZValue(-1);
        enemyTank->setEnemy(playerTank);

        connect(timerGame, &QTimer::timeout, enemyTank, &EnemyTank::slotAction);
        connect(enemyTank, &EnemyTank::signalShot, this, &Widget::slotCreateShot);
    }
    else {
        playerTank = new PlayerTank();
        listTanks.append(playerTank);
        map->addItem(playerTank);
        playerTank->setPos(placeAppearance);
        playerTank->setZValue(-1);

        connect(timerGame, &QTimer::timeout, playerTank, &PlayerTank::slotAction);
//        timerGame->start(1000 / 80);
        timerGame->start(12);

        connect(playerTank, &PlayerTank::signalShot, this, &Widget::slotCreateShot);
    }
}

void Widget::slotChooseButton(Button *button)
{
    foreach (Button *itemButton, vecButton) {
        if(itemButton == button) {
            itemButton->setIsChoose(true);
        }
        else {
            itemButton->setIsChoose(false);
        }
    }
}

void Widget::loseLife()
{
    map->removeItem(playerTank);

    if(!vecHeart.isEmpty()) {
        HeartSymbol *heart = vecHeart.back();
        description->removeItem(heart);
        vecHeart.pop_back();
        delete heart;

        if(!vecHeart.isEmpty()) {
            map->addItem(playerTank);
            playerTank->setPos(-125, 325);
            emit playerTank->slotSetBreak();
        }
        else {
            gameOver();
        }
    }
}

void Widget::clearAll()
{
    foreach (QGraphicsItem* item, listBrickWall) {
        map->removeItem(item);
        listBrickWall.removeOne(item);
        delete item;
    }

    foreach (QGraphicsItem* item, listConcreteWall) {
        map->removeItem(item);
        listConcreteWall.removeOne(item);
        delete item;
    }

    foreach (Shell* item, listShells) {
        emit item->signalDelete(item);
    }

    foreach (Tank* item, listTanks) {
        map->removeItem(item);
        listTanks.removeOne(item);
        delete item;
    }

    foreach (TankSymbol *symbol, vectorTankSymbol) {
        description->removeItem(symbol);
        vectorTankSymbol.removeOne(symbol);
        delete symbol;
    }

    foreach (HeartSymbol *hsymbol, vecHeart) {
        description->removeItem(hsymbol);
        vecHeart.removeOne(hsymbol);
        delete hsymbol;
    }

    foreach (Appearance *appear, listAppearance) {
        map->removeItem(appear);
        listAppearance.removeOne(appear);
        delete appear;
    }

    foreach (Ruin *ruin, listRuin) {
        map->removeItem(ruin);
        listRuin.removeOne(ruin);
        delete ruin;
    }

    foreach (Emblem *img, listImage) {
        map->removeItem(img);
        listImage.removeOne(img);
        delete img;
    }
}

void Widget::startGame()
{
    if(stateProg == MENU) {
        closeMenu();
    }

    createMap();
    createDiscription();

    Appearance *appearance = new Appearance(false);
    listAppearance.append(appearance);
    map->addItem(appearance);
    appearance->setPos(-125, 325);
    connect(appearance, &Appearance::sigEndExist, this, &Widget::slotDeleteAppearance);

    //createSoundAppearance();

    Emblem *emblem = new Emblem();
    listImage.append(emblem);
    map->addItem(emblem);
    emblem->setPos(0,300);
    isEmblem = true;

    timeNextAppearance = 4000;

    countEnemyTanks = 10;
    countEnemyTanksLight = 2;
    countEnemyTanksMedium = 6;
    countEnemyTanksHard = 2;
    countTypeEnemyTanks[0] = 2;
    countTypeEnemyTanks[1] = 6;
    countTypeEnemyTanks[2] = 2;
    timerAppearTanks = new QTimer();
    connect(timerAppearTanks, &QTimer::timeout, this, &Widget::slotCreateEnemyTanks);
    timerAppearTanks->start(timeNextAppearance);

    timerCheckOver = new QTimer();
    connect(timerCheckOver, &QTimer::timeout, this, &Widget::slotCheckGameOver);
//    timerCheckOver->start(2000);

//    connect(this, &Widget::signalGameOver, this, &Widget::slotGameOver);
    qsrand(time(NULL));
}

void Widget::createSoundAppearance()
{
    QMediaPlayer *playerElectricity;
    QMediaPlaylist *playlistElectricity;
    playerElectricity = new QMediaPlayer(this);
    playlistElectricity = new QMediaPlaylist(playerElectricity);
    playerElectricity->setPlaylist(playlistElectricity);
    playlistElectricity->addMedia(QUrl("qrc:/sound/Sounds/sound_electricity.wav"));
    playlistElectricity->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playerElectricity->setVolume(30);
    playerElectricity->play();
}

void Widget::createSoundShot()
{
    QMediaPlayer *playerShot;
    QMediaPlaylist *playlistShot;
    playerShot = new QMediaPlayer(this);
    playlistShot = new QMediaPlaylist(playerShot);
    playerShot->setPlaylist(playlistShot);
    playlistShot->addMedia(QUrl("qrc:/sound/Sounds/TankShot2.wav"));
    playlistShot->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playerShot->setVolume(50);
    playerShot->play();
}

void Widget::createSoundBlow()
{
    QMediaPlayer *playerBlow = new QMediaPlayer();
    QMediaPlaylist *playlistBlow = new QMediaPlaylist(playerBlow);
    playerBlow->setPlaylist(playlistBlow);
    playlistBlow->addMedia(QUrl("qrc:/sound/Sounds/sound_blow_2.wav"));
    playlistBlow->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playerBlow->play();
}

void Widget::setResize()
{
    int w = this->size().width();
    int h = this->size().height();
    int wNew, hNew, wNew2, hNew2;
    double wR, hR, wR2, hR2;
    std::tie(wNew, hNew, wR, hR, wNew2, hNew2, wR2, hR2) = mWindowCounter.getNewSizeMode(w, h);
//    std::tie(wNew, hNew, wR, hR) = mWindowCounter.getNewSize(w, h);
//    WindowValues wind = mWindowCounter.getNewSize0(w, h);

    int x1 = (w - (wNew + wNew2 + w * 0.03)) / 2;
//    int y1 = (h - (hNew + hNew2)) / 2;
    int y1 = 0;
    ui->graphicsView->setGeometry(x1, y1, wNew, hNew);
//    ui->graphicsView->resize(wNew, hNew);
    ui->graphicsView->scale(wR, hR);
//    ui->graphicsView_2->resize(wNew2, hNew2);
    int x2 = ui->graphicsView->x() + wNew;
    int y2 = ui->graphicsView->y();
    ui->graphicsView_2->setGeometry(x2, y2, wNew2, hNew2);
    ui->graphicsView_2->scale(wR2, hR2);
//    ui->graphicsView->resize(wind.w1, wind.h1);
//    if(isResize) ui->graphicsView->scale(wind.xRate1, wind.yRate1);
}

void Widget::createMap()
{
    //QVector<QVector<int>> mapIt;
    int mapIt[28][28];

    /*QVector<QVector<int>> mapIt1*/int mapIt1[28][28] = {
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {2,2,0,0,1,1,2,2,1,1,0,0,2,2,2,2,0,0,1,1,2,2,1,1,0,0,2,2},
       {2,2,0,0,1,1,2,2,1,1,0,0,2,2,2,2,0,0,1,1,2,2,1,1,0,0,2,2},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0},
       {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0}
   };

    /*QVector<QVector<int>> mapIt2*/int mapIt2[28][28]={
       {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
       {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,2,2,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
       {1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
       {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
       {0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0},
       {0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0},
       {0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0},
       {2,2,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,2,2},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
       {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,2,2,0,0,0,0,2,2,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0},
       {0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0},
       {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0},
       {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0},
       {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0}
   };

    switch (level) {
    case 1:
        //mapIt=mapIt1;
        memcpy(mapIt,mapIt1,(28*28)*sizeof(int));
        break;
    case 2:
        //mapIt=mapIt2;
        memcpy(mapIt,mapIt2,(28*28)*sizeof(int));
        break;
    default:
        break;
    }

    for(int i=0;i<28;i++)
    {
        for(int j=0;j<28;j++)
        {
            if(mapIt[j][i]==1)
            {
                BrickWall *wall=new BrickWall();
                listBrickWall.append(wall);
                map->addItem(wall);
                wall->setPos((i*25-350),(j*25-350));
            }

            if(mapIt[j][i]==2)
            {
                ConcreteWall *concreteWall=new ConcreteWall();
                listConcreteWall.append(concreteWall);
                map->addItem(concreteWall);
                concreteWall->setPos((i*25-350),(j*25-350));
            }
        }
    }
}

QPoint Widget::countPos()
{
    int minus = qrand() % 2 + 1;
    int n = 0;

    if(minus == 2) {
        minus =- 1;
        n = 1;
    }

    int xTank=((qrand()%7+n)*minus*50)+25;
    int yTank=-350-(-25);

    return QPoint(xTank,yTank);
}

void Widget::createDiscription()
{
    int p[10][2]={
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0}
    };

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(p[i][j]==1)
            {
                TankSymbol *symbol=new TankSymbol();
                vectorTankSymbol.append(symbol);
                description->addItem(symbol);
                symbol->setPos((j * 40 - 32), (i * 40 - 300));
            }
        }
    }

    for(int i=0; i<mNumberLives; i++)
    {
        HeartSymbol *hsymbol = new HeartSymbol();
        vecHeart.append(hsymbol);
        description->addItem(hsymbol);
        hsymbol->setPos((i * 35 - 31), 200);
    }
}

void Widget::openMenu()
{
    ui->groupBoxWindow->hide();
    ui->groupBoxLevel->hide();
    ui->groupBoxMenu->show();
    QColor colorMenu = QColor(0, 200, 110).darker(200);

    pal.setColor(this->backgroundRole(), colorMenu);
    this->setPalette(pal);

    pal.setColor(ui->graphicsView->backgroundRole(), colorMenu);
    ui->graphicsView->setPalette(pal);

//    pal.setColor(ui->graphicsView_2->backgroundRole(), QColor(0, 200, 110));
    pal.setColor(ui->graphicsView_2->backgroundRole(), QColor(0, 0, 0));
    ui->graphicsView_2->setPalette(pal);

    int p =- 125;

    foreach (Button *button, vecButton) {
        map->addItem(button);
        button->setPos(-100, p);
        //connect(this,&Widget::sigChoose,button,&Button::slotChoose);
        connect(button, &Button::sigIsChoose, this,&Widget::slotChooseButton);
        connect(button, &Button::sigClicked, this,&Widget::slotClickEnter);
        p += 100;
    }

    vecButton.first()->setIsChoose(true);

//    connect(keyUp, &QShortcut::activated, this, &Widget::slotClickUp);
//    connect(keyDown, &QShortcut::activated, this, &Widget::slotClickDown);

    //playerMenu->play();
    stateProg = MENU;
}

void Widget::closeMenu()
{
    ui->groupBoxWindow->show();
//    setResize();

    QColor colorEnv = QColor(0,0,0).darker(200);

    pal.setColor(this->backgroundRole(), colorEnv);
    this->setPalette(pal);

    pal.setColor(ui->graphicsView->backgroundRole(), QColor(255, 200, 110).darker(200));
    ui->graphicsView->setPalette(pal);

    pal.setColor(ui->graphicsView_2->backgroundRole(), QColor(0, 200, 110));
//    pal.setColor(ui->graphicsView_2->backgroundRole(), colorEnv);
    ui->graphicsView_2->setPalette(pal);

    foreach (Button *button, vecButton) {
        map->removeItem(button);
        //disconnect(this,&Widget::sigChoose,button,&Button::slotChoose);
        disconnect(button,&Button::sigIsChoose,this,&Widget::slotChooseButton);
        disconnect(button,&Button::sigClicked,this,&Widget::slotClickEnter);
    }
//    disconnect(keyUp,&QShortcut::activated,this,&Widget::slotClickUp);
//    disconnect(keyDown,&QShortcut::activated,this,&Widget::slotClickDown);

    playerMenu->stop();
    stateProg = GAME;
}

void Widget::on_butStart_clicked()
{
    ui->groupBoxMenu->hide();
    ui->groupBoxLevel->hide();
    startGame();
}

void Widget::on_butLoad_clicked()
{
    ui->groupBoxMenu->hide();
    ui->groupBoxLevel->show();
}

void Widget::on_butBack_clicked()
{
    ui->groupBoxLevel->hide();
    ui->groupBoxMenu->show();
}

void Widget::on_butLevel_1_clicked()
{
    ui->groupBoxMenu->hide();
    ui->groupBoxLevel->hide();
    startGame();
}

void Widget::on_butLevel_2_clicked()
{
    level = 2;
    ui->groupBoxMenu->hide();
    ui->groupBoxLevel->hide();
    startGame();
}
