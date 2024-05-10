#include "target.h"

Target::Target(int iX, int iY,QMainWindow* pWindow)
{
    m_pWindow = pWindow;

    m_pImg = new QLabel(m_pWindow);
    m_pImg->setPixmap(QPixmap("C:\\Imgs\\target.jpg"));
    this->setPosition(iX, iY);
    m_pImg->setVisible(true);
}
Target::~Target()
{
    delete m_pImg;
}
int Target::getX()
{
    return m_iX;
}
int Target::getY()
{
    return m_iY;
}
void Target::setPosition(int iX, int iY)
{
    m_iX = iX;
    m_iY = iY;
    m_pImg->setGeometry(iX*TILE_WIDTH, iY*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
}

