#ifndef WINDOWCOUNTER_H
#define WINDOWCOUNTER_H

#include <tuple>
const int W1 = 700;
const int W2 = 100;
const int H_Window = 700;

struct WindowValues
{
    int w1;
    int h1;
    double xRate1;
    double yRate1;
    int w2;
    int h2;
    double xRate2;
    double yRate2;

    WindowValues(int w1, int h1, double xR1, double yR1, int w2, int h2, double xR2, double yR2) {
        this->w1 = w1;
        this->h1 = h1;
        xRate1 = xR1;
        yRate1 = yR1;
        this->w2 = w2;
        this->h2 = h2;
        xRate2 = xR2;
        yRate2 = yR2;
    }
};

class WindowCounter
{
public:
    WindowCounter();
    void setSizeWindow(double w, double h, double w2);
    bool setNewSize(int &w, int &h, double &wRate, double &hRate);
    std::tuple<int, int, double, double> getNewSize(int w, int h);
    std::tuple<int, int, double, double, int, int, double, double> getNewSizeMode(int w, int h);
    WindowValues getNewSize0(int w, int h);
    bool getContedSize(int &w, int &h, double &wRate, double &hRate);

private:
    double mWidthWindow;
    double mHeightWindow;
    double mWidthWindow2;
    double mHeightWindow2;
    double mRate;
//    double mTempWidth;
//    double mTempHeight;
};

#endif // WINDOWCOUNTER_H
