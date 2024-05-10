#ifndef PLAYER_H
#define PLAYER_H

#include<QMainWindow>
#include<QLabel>
#include<QPixmap>

class Player
{
private:
    int m_iX;
    int m_iY;

public:

    QMainWindow* m_pWindow;
    QLabel* m_pImg;

    Player(int iX, int iY, QMainWindow* pWindow);
    ~Player();

    //void movePlayer();
    int getX();
    int getY();

    void setPosition(int iX, int iY);
};

#endif // PLAYER_H
