#ifndef TARGET_H
#define TARGET_H
#include<QMainWindow>
#include<QLabel>
#include "Constants.h"

class Target
{
private:
    int m_iX;
    int m_iY;

public:

    QMainWindow* m_pWindow;
    QLabel* m_pImg;

    Target(int iX, int iY, QMainWindow* pWindow);
    ~Target();

    int getX();
    int getY();

    void setPosition(int iX, int iY);
};

#endif // TARGET_H
