#include "enemy.h"
#include "Constants.h"


Enemy::Enemy(int iX, int iY, QMainWindow* pWindow)
{
    m_iX = iX;
    m_iY = iY;
    m_pWindow = pWindow;
    m_pImg = new QLabel(m_pWindow);
    m_pImg->setPixmap(QPixmap("C:\\Imgs\\enemy.jpg"));
    m_pImg->setGeometry(m_iX * TILE_WIDTH, m_iY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
    m_pImg->setVisible(true);
}

Enemy::~Enemy()
{
    delete m_pImg;
}

int Enemy::getX()
{
    return m_iX;
}
int Enemy::getY()
{
    return m_iY;
}

void Enemy::setPosition(int iX, int iY)
{
    m_iX = iX;
    m_iY = iY;
    m_pImg->setGeometry(iX*TILE_WIDTH, iY*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
}


