#ifndef ENEMY_H
#define ENEMY_H

#include<QMainWindow>
#include<QLabel>
#include<QPixmap>
#include "Constants.h"

class Enemy
{
private:
    int m_iX;
    int m_iY;

public:

    QMainWindow* m_pWindow;
    QLabel* m_pImg;

    Enemy(int iX, int iY, QMainWindow* pWindow);
    ~Enemy();

    int getX();
    int getY();
    void setPixmap(const QString& imagePath);
    void setPosition(int iX, int iY);
};

#endif // ENEMY_H
