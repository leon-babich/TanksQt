#ifndef MYOBJ_H
#define MYOBJ_H

#include <windows.h>

#include "tank.h"

class PlayerTank : public Tank
{
    Q_OBJECT
public:
    explicit PlayerTank(QObject *parent = 0);
    ~PlayerTank();
    bool getIsReadyShot() const;
    void setIsReadyShot(bool);
    void addShell(Shell *shell);
    void clearShell();
    Shell* getShell() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotAction();
    void slotAdmissionMove();

public:


private:
    QTimer *timerClick;
    int countTimeClick;
    Shell* m_shell;

private:
    bool helpMove();
};

#endif // MYOBJ_H
