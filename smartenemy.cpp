#include "smartenemy.h"

SmartEnemy::SmartEnemy(int iX, int iY, QMainWindow* pWindow)
{
    m_iX = iX;
    m_iY = iY;
    m_iDirection = 0;
    m_pWindow = pWindow;
    m_pImg = new QLabel(m_pWindow);
    m_pImg->setPixmap(QPixmap("C:\\Imgs\\enemy.jpg"));
    m_pImg->setGeometry(m_iX * TILE_WIDTH, m_iY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
    m_pImg->setVisible(true);
}

SmartEnemy::~SmartEnemy()
{
    delete m_pImg;
}

int SmartEnemy::getX()
{
    return m_iX;
}
int SmartEnemy::getY()
{
    return m_iY;
}


int SmartEnemy::getDirection()
{
    return m_iDirection;
}
void SmartEnemy::setDirection(int iDirection)
{
    m_iDirection = iDirection;
}

void SmartEnemy::setPosition(int iX, int iY)
{
    m_iX = iX;
    m_iY = iY;
    m_pImg->setGeometry(iX*TILE_WIDTH, iY*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
}
