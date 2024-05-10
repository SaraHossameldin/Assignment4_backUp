#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <QQueue>
#include <QVector>
#include <utility>

#define MAZE_HEIGHT 20
#define MAZE_WIDTH 20

struct Point {
    int x, y;
};

QVector<Point> FindShortestPath(char grid[MAZE_HEIGHT][MAZE_WIDTH], Point src, Point dest);
#endif // SHORTESTPATH_H
