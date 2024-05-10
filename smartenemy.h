#ifndef SMARTENEMY_H
#define SMARTENEMY_H
#include<QMainWIndow>
#include<QLabel>
#include "Constants.h"

class SmartEnemy
{
private:
    int m_iX;
    int m_iY;
    int m_iDirection;
public:

    QMainWindow* m_pWindow;
    QLabel* m_pImg;

    SmartEnemy(int iX, int iY, QMainWindow* pWindow);
    ~SmartEnemy();

    int getX();
    int getY();
    void setPixmap(const QString& imagePath);
    void setPosition(int iX, int iY);

    int getDirection();
    void setDirection(int iDirection);
};

#endif // SMARTENEMY_H
