#include "player.h"
#include "Constants.h"


Player::Player(int iX, int iY, QMainWindow* pWindow)
{
    m_pWindow = pWindow;

    m_pImg = new QLabel(m_pWindow);
    m_pImg->setPixmap(QPixmap("C:\\Imgs\\player.jpg"));
    this->setPosition(iX, iY);
    m_pImg->setVisible(true);
}

Player::~Player()
{
    delete m_pImg;
}

int Player::getX()
{
    return m_iX;
}
int Player::getY()
{
    return m_iY;
}

void Player::setPosition(int iX, int iY)
{
    m_iX = iX;
    m_iY = iY;
    m_pImg->setGeometry(iX*TILE_WIDTH, iY*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
}
