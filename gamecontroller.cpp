#include "gamecontroller.h"
#include "MazeLevels.h"
#include "Constants.h"
#include "shortestpath.h"

#include<QKeyEvent>
#include<QMessageBox>
#include<exception>
#include <QMap>

int CosDegree(int iDegree)
{
    iDegree = iDegree % 360;
    switch (iDegree)
    {
    case 0:
        return 1;
    case 90:
        return 0;
    case 180:
        return -1;
    case 270:
        return 0;
    }
    return 0;
}

int SinDegree(int iDegree)
{
    iDegree = iDegree % 360;
    switch (iDegree)
    {
    case 0:
        return 0;
    case 90:
        return 1;
    case 180:
        return 0;
    case 270:
        return -1;
    }
    return 0;
}

GameController::GameController(int iLevel, int iHealth, QMainWindow *pWindow)
{
    m_pPlayer = nullptr;
    m_pTarget = nullptr;
    m_iHealth = iHealth;
    m_pWindow = pWindow;
    m_iLevel = iLevel;

    this->setupNewLevel();
}

void GameController::initialize2DGrid()
{
    for (int i = 0; i < MAZE_HEIGHT; i++)
        for(int j = 0; j < Maze_WIDTH ; j++)
            m_arrCurrentLevel[i][j] = Levels[m_iLevel][i][j];
}

void GameController::keyPressEvent(QKeyEvent* event)
{
    // Get the current position of the player
    int iX = m_pPlayer->getX();
    int iY = m_pPlayer->getY();

    // Handle the key press events
    if (event->key() == Qt::Key_Right)
    {
        if (iX + 1 < Maze_WIDTH && m_arrCurrentLevel[iY][iX + 1] != 'W')
        {

            m_pPlayer->setPosition(iX + 1, iY);
            showShortestPath();
        }
    }
    else if (event->key() == Qt::Key_Left)
    {
        if (iX - 1 >= 0 && m_arrCurrentLevel[iY][iX - 1] != 'W')
        {

            m_pPlayer->setPosition(iX - 1, iY);
            showShortestPath();
        }
    }
    else if (event->key() == Qt::Key_Up)
    {
        if (iY - 1 >= 0 && m_arrCurrentLevel[iY - 1][iX] != 'W')
        {

            m_pPlayer->setPosition(iX, iY - 1);
            showShortestPath();
        }
    }
    else if (event->key() == Qt::Key_Down)
    {
        if (iY + 1 < MAZE_HEIGHT && m_arrCurrentLevel[iY + 1][iX] != 'W')
        {

            m_pPlayer->setPosition(iX, iY + 1);
            showShortestPath();
        }
    }

    this->handlePlayerCollision(false);
}

void GameController::handlePlayerCollision(bool bOnlyEnemy)
{
    //If the player collides with the enemy
    if (!bOnlyEnemy &&
        m_pPlayer->getX() == m_pTarget->getX() &&
        m_pPlayer->getY() == m_pTarget->getY())
    {
        ShowNextLevel();
    }
    for (auto iter = m_lstEnemy.begin(); iter != m_lstEnemy.end(); iter++)
    {
        Enemy* pEnemy = (Enemy*)(*iter);
        if (pEnemy->getX() == m_pPlayer->getX() &&
            pEnemy->getY() == m_pPlayer->getY() )
        {
            //Handle collision
            m_iHealth--;
            if(m_iHealth <= 0)
            {
                showGameOver();
            }
        }
    }
    for (auto iter = m_lstSmartEnemy.begin();
         iter != m_lstSmartEnemy.end();
         iter++)
    {
        SmartEnemy* pEnemy = (SmartEnemy*)(*iter);
        if (pEnemy->getX() == m_pPlayer->getX() &&
            pEnemy->getY() == m_pPlayer->getY() )
        {
            //Handle collision
            m_iHealth--;
            if(m_iHealth <= 0)
            {
                showGameOver();
            }
        }
    }
}

void GameController::showGameOver()
{
    QMessageBox::information(m_pWindow,"Game Over","The game is over. Try again!");
    for (int i = 0; i < MAZE_HEIGHT; i++)
        for(int j = 0; j < Maze_WIDTH ; j++)
            if (m_arrCurrentLevel[i][j] == 'P')
                m_pPlayer->setPosition(j, i);
    m_iHealth = 3;
}

void GameController::setupNewLevel()
{
    m_pPlayer = nullptr;
    m_pTarget = nullptr;

    this->initialize2DGrid();

    //loop through m_arrCurrentLevel
    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for(int j = 0; j < Maze_WIDTH ; j++)
        {
            if (m_arrCurrentLevel[i][j] == 'E')
            {
                Enemy* enemy = new Enemy(j, i, m_pWindow);

                m_lstEnemy.append(enemy);
            }
            else if (m_arrCurrentLevel[i][j] == 'S')
            {
                SmartEnemy* senemy = new SmartEnemy(j, i, m_pWindow);

                m_lstSmartEnemy.append(senemy);
            }
            else if (m_arrCurrentLevel[i][j] == 'P')
            {
                if (m_pPlayer == nullptr)
                    m_pPlayer = new Player(j, i, m_pWindow);
                else
                {
                    QMessageBox::critical(nullptr,"Error","There are multiple players found in the game");
                    m_pWindow->close();
                }
            }
            else if (m_arrCurrentLevel[i][j] == 'T')
            {
                if (m_pTarget == nullptr)
                    m_pTarget = new Target(j, i,m_pWindow);
                else
                {
                    QMessageBox::critical(nullptr,"Error","There are multiple targets found in the game");
                    m_pWindow->close();
                }
            }
        }
    }

    if (m_pPlayer==nullptr)
    {
        QMessageBox::critical(nullptr,"Error","There is no player found in the game");
        m_pWindow->close();
    }
    if (m_pTarget==nullptr)
    {
        QMessageBox::critical(nullptr,"Error","There is no target found in the game");
        m_pWindow->close();
    }

    //build maze ui
    this->buildStaticWalls();
}
void GameController::ShowNextLevel()
{
    QMessageBox::critical(m_pWindow,"Congratulation","Press OK to go to next level");
    m_iLevel++;
    m_iLevel = m_iLevel % NUM_LEVELS;
    for (auto iter = m_lstWall.begin(); iter != m_lstWall.end(); iter++)
    {
        QLabel* pItem = (QLabel*)*iter;
        delete pItem;
    }
    m_lstWall.clear();
    for (auto iter = m_lstEnemy.begin(); iter != m_lstEnemy.end(); iter++)
    {
        Enemy* pEnemy = (Enemy*)(*iter);
        delete pEnemy;
    }
    m_lstEnemy.clear();
    for (auto iter = m_lstSmartEnemy.begin(); iter != m_lstSmartEnemy.end(); iter++)
    {
        SmartEnemy* pEnemy = (SmartEnemy*)(*iter);
        delete pEnemy;
    }
    m_lstSmartEnemy.clear();

    delete m_pTarget;
    delete m_pPlayer;
    m_pTarget = nullptr;
    m_pPlayer = nullptr;

    //initialize2DGrid(m_iLevel+1);

    m_iHealth=3;
    this->setupNewLevel();
}

void GameController::updateGame()
{
    for (auto iter = m_lstSmartEnemy.begin();
         iter != m_lstSmartEnemy.end();
         iter++)
    {
        SmartEnemy* pEnemy = (SmartEnemy*)(*iter);
        int iX = pEnemy->getX();
        int iY = pEnemy->getY();
        int iInitDir = pEnemy->getDirection();

        for (int iDir = 0; iDir < 360; iDir+=90)
        {
            int iNewX = iX + CosDegree(iDir + iInitDir);
            int iNewY = iY + SinDegree(iDir + iInitDir);

            if (iNewX < Maze_WIDTH  && iNewY < MAZE_HEIGHT &&
                m_arrCurrentLevel[iNewY][iNewX] != 'W' )
            {
                pEnemy->setPosition(iNewX, iNewY);
                pEnemy->setDirection(iInitDir + iDir);
                break;
            }
        }
    }
    handlePlayerCollision(true);
}

void GameController::buildStaticWalls()
{
    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for(int j = 0; j < Maze_WIDTH ; j++)
        {
            if (m_arrCurrentLevel[i][j] == 'W')
            {
                QLabel * pImg = new QLabel(m_pWindow);
                pImg->setPixmap(QPixmap("C:\\Imgs\\wall.jpg"));
                pImg->setGeometry(j*TILE_WIDTH, i*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
                m_lstWall.append(pImg);
                pImg->setVisible(true);
            }
        }
    }
}
void GameController::showShortestPath()
{
    for (auto iter = m_lstShortestPath.begin(); iter != m_lstShortestPath.end(); iter++)
    {
        QLabel* pItem = (QLabel*)*iter;
        delete pItem;
    }
    m_lstShortestPath.clear();

    QVector<Point> vecNewPath = FindShortestPath(m_arrCurrentLevel,
                                                 {m_pPlayer->getY(), m_pPlayer->getX()},
                                                 {m_pTarget->getY(), m_pTarget->getX()});
    for (auto iter = vecNewPath.begin(); iter != vecNewPath.end(); iter++)
    {
        Point p1 = *iter;
        if (p1.y == m_pPlayer->getX() && p1.x == m_pPlayer->getY())
            continue;
        if (p1.y == m_pTarget->getX() && p1.x == m_pTarget->getY())
            continue;
        QLabel * pImg = new QLabel(m_pWindow);
        pImg->setPixmap(QPixmap("C:\\Imgs\\dot.jpg"));
        pImg->setGeometry((p1.y)*TILE_WIDTH, (p1.x)*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
        m_lstShortestPath.append(pImg);
        pImg->setVisible(true);
    }
}
