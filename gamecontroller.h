#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include"player.h"
#include "enemy.h"
#include "smartenemy.h"
#include "target.h"
#include <QMainWindow>
#include <QList>
#include<QKeyEvent>

class GameController
{
private:
    QMainWindow* m_pWindow;
    Player* m_pPlayer;
    Target* m_pTarget;
    QList<Enemy*> m_lstEnemy;
    QList<SmartEnemy*> m_lstSmartEnemy;
    QList<QLabel*> m_lstWall;
    QList<QLabel*> m_lstShortestPath;
    int m_iHealth;
    int m_iLevel;
    char m_arrCurrentLevel[20][20];

    void setupNewLevel();
    void initialize2DGrid();
    void buildStaticWalls();
    void showShortestPath();

public:
    //Constructor
    GameController(int iLevel, int iHealth, QMainWindow *pWindow);

    //Functions
    void start();
    void keyPressEvent(QKeyEvent* event);
    //void checkPlayerBounds();
    void checkSmartEnemyBounds();
    void convert2DGridtoGraph();
    void findShortestPath();
    void handlePlayerCollision(bool bOnlyEnemy);
    //void handlePlayerandSmartEnemyCollision();
    void displayHealth();
    void showGameOver();
    void ShowNextLevel();

    void updateGame();
};

#endif // GAMECONTROLLER_H
