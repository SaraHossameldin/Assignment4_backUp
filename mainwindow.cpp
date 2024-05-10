#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pGame = new GameController(0, 3, this);
    m_pTimer = new QTimer(this);

    connect(m_pTimer, &QTimer::timeout, this, &MainWindow::onTimer);
    m_pTimer->start(1000);
}

void MainWindow::onTimer()
{
    m_pGame->updateGame();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    m_pGame->keyPressEvent(event);
}

MainWindow::~MainWindow()
{
    delete m_pTimer;
    delete m_pGame;
    delete ui;
}
