#ifndef DIALOGLEVEL_H
#define DIALOGLEVEL_H

#include <QDialog>

namespace Ui {
class DialogLevel;
}

class DialogLevel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLevel(QWidget *parent = 0);
    ~DialogLevel();

private:
    Ui::DialogLevel *ui;
};

#endif // DIALOGLEVEL_H
