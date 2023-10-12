#include "dialoglevel.h"
#include "ui_dialoglevel.h"

DialogLevel::DialogLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLevel)
{
    ui->setupUi(this);
}

DialogLevel::~DialogLevel()
{
    delete ui;
}
