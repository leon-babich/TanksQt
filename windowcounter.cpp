#include "windowcounter.h"

WindowCounter::WindowCounter()
{
    mWidthWindow = 0;
    mHeightWindow = 0;
}

void WindowCounter::setSizeWindow(double w, double h, double w2)
{
    mWidthWindow = w;
    mHeightWindow = h;
    mWidthWindow2 = w2;
    mHeightWindow2 = h;
    mRate = w / w2;
}

bool WindowCounter::setNewSize(int &w, int &h, double &wRate, double &hRate)
{
    if(mWidthWindow == 0.0 || mHeightWindow == 0.0) {
        return false;
    }

    int s;
    double r = (double)(W1 + W2) / H_Window * 1.1;
    //s = w < h ? w : h;
    if(w < h) {
        w /= r;
        h = w;
    }
    else if((double)w / h >= r){
        w = h;
    }
    else {
        w *= (double)h / w * 1.1;
        h = w;
    }
    //w = s; h = s;
    wRate = w / mWidthWindow;
    hRate = h / mHeightWindow;
    mWidthWindow = w;
    mHeightWindow = h;

    return true;
}

std::tuple<int, int, double, double> WindowCounter::getNewSize(int w, int h)
{
    int s;
    int wNew, hNew;
    s = w < h ? w : h;
    wNew = hNew = s;
    double wRate = wNew / mWidthWindow;
    double hRate = hNew / mHeightWindow;
    mWidthWindow = wNew;
    mHeightWindow = hNew;

    return std::make_tuple(wNew, hNew, wRate, hRate);
}

std::tuple<int, int, double, double, int, int, double, double> WindowCounter::getNewSizeMode(int w, int h)
{
    int s;
    int wNew, hNew, wNew2, hNew2;
    double wRate, hRate, wRate2, hRate2;

    s = w < h ? w : h;
    s *= 0.97;

    hNew = hNew2 = s;
    wNew2 = s / (mRate - 1);
    wNew = (s - wNew2) * 0.97;

    wRate = wNew / mWidthWindow;
    hRate = hNew / mHeightWindow;
    wRate2 = wNew2 / mWidthWindow2;
    hRate2 = hNew2 / mHeightWindow2;
    mWidthWindow = wNew;
    mHeightWindow = hNew;
    mWidthWindow2 = wNew2;
    mHeightWindow2 = hNew2;

    return std::make_tuple(wNew, hNew, wRate, hRate, wNew2, hNew2, wRate2, hRate2);
}

WindowValues WindowCounter::getNewSize0(int w, int h)
{
    int s;
    int wNew, hNew, wNew2, hNew2;
    double wRate, hRate, wRate2, hRate2;
    s = w < h ? w : h;
    wNew = hNew = s;
    wRate = wNew / mWidthWindow;
    hRate = hNew / mHeightWindow;
    mWidthWindow = wNew;
    mHeightWindow = hNew;

    return WindowValues(wNew, hNew, wRate, hRate, wNew2, hNew2, wRate2, hRate2);
}

bool WindowCounter::getContedSize(int &w, int &h, double &wRate, double &hRate)
{
//    if(mWidthWindow == 0.0 || mHeightWindow == 0.0 || (mWidthWindow == mTempWidth && mHeightWindow == mTempHeight)) {
//        return false;
//    }

//    int s = mTempWidth < mTempHeight ? mTempWidth : mTempHeight;
//    w = s; h = s;
//    wRate = w / mWidthWindow;
//    hRate = h / mHeightWindow;
//    mWidthWindow = w;
//    mHeightWindow = h;

    return true;
}
