#include "shortestpath.h"

struct Node {
    Point pt;
    int dist;
    Node* parent;
};

bool isValid(int row, int col) {
    return (row >= 0) && (row < MAZE_HEIGHT) && (col >= 0) && (col < MAZE_WIDTH);
}

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

QVector<Point> FindShortestPath(char grid[MAZE_HEIGHT][MAZE_WIDTH], Point src, Point dest) {
    bool visited[MAZE_HEIGHT][MAZE_WIDTH];
    memset(visited, false, sizeof visited);

    visited[src.x][src.y] = true;

    QQueue<Node*> q;

    Node* s = new Node{src, 0, nullptr};
    q.enqueue(s);

    Node* reachedEnd = nullptr;

    while (!q.empty()) {
        Node* curr = q.front();
        Point pt = curr->pt;

        if (pt.x == dest.x && pt.y == dest.y) {
            reachedEnd = curr;
            break;
        }

        q.dequeue();

        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col) && grid[row][col] != 'W' && !visited[row][col]) {
                visited[row][col] = true;
                Node* adjCell = new Node{{row, col}, curr->dist + 1, curr};
                q.enqueue(adjCell);
            }
        }
    }

    // Backtrack from destination to source using parent pointers
    QVector<Point> path;
    while (reachedEnd != nullptr) {
        path.push_back(reachedEnd->pt);
        reachedEnd = reachedEnd->parent;
    }

    // Clean up memory
    while (!q.empty()) {
        delete q.front();
        q.dequeue();
    }

    // Reverse the path to start from the source
    std::reverse(path.begin(), path.end());

    return path;
}
