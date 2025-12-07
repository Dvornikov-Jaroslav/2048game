#include "game2048.hpp"
#include <cstring>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

Game2048::Game2048(QObject *parent) : QObject(parent) {
    QFile file("bestscore.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> bestScore;
        file.close();
    }
}

void Game2048::newGame() {
    std::memset(board, 0, sizeof(board));
    score = 0;
    addRandomTile();
    addRandomTile();
}

void Game2048::addRandomTile() {
    struct Pos { int r, c; };
    QVector<Pos> empty;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0) empty.append({i, j});

    if (empty.isEmpty()) return;

    auto pos = empty.at(QRandomGenerator::global()->bounded(empty.size()));
    board[pos.r][pos.c] = (QRandomGenerator::global()->bounded(10) < 9) ? 2 : 4;
}

bool Game2048::moveLeft() {
    bool moved = false;
    for (int i = 0; i < 4; ++i) {
        int lastMerge = -1;
        for (int j = 1; j < 4; ++j) {
            if (board[i][j] == 0) continue;
            int k = j;
            while (k > 0 && board[i][k - 1] == 0) {
                board[i][k - 1] = board[i][k];
                board[i][k] = 0;
                k--;
                moved = true;
            }
            if (k > 0 && board[i][k - 1] == board[i][k] && lastMerge != k - 1) {
                board[i][k - 1] *= 2;
                score += board[i][k - 1];
                board[i][k] = 0;
                lastMerge = k - 1;
                moved = true;
            }
        }
    }
    updateBestScore();
    return moved;
}

bool Game2048::moveRight() {
    bool moved = false;
    for (int i = 0; i < 4; ++i) {
        int lastMerge = 4;
        for (int j = 2; j >= 0; --j) {
            if (board[i][j] == 0) continue;
            int k = j;
            while (k < 3 && board[i][k + 1] == 0) {
                board[i][k + 1] = board[i][k];
                board[i][k] = 0;
                k++;
                moved = true;
            }
            if (k < 3 && board[i][k + 1] == board[i][k] && lastMerge != k + 1) {
                board[i][k + 1] *= 2;
                score += board[i][k + 1];
                board[i][k] = 0;
                lastMerge = k + 1;
                moved = true;
            }
        }
    }
    updateBestScore();
    return moved;
}

bool Game2048::moveUp() {
    bool moved = false;
    for (int j = 0; j < 4; ++j) {
        int lastMerge = -1;
        for (int i = 1; i < 4; ++i) {
            if (board[i][j] == 0) continue;
            int k = i;
            while (k > 0 && board[k - 1][j] == 0) {
                board[k - 1][j] = board[k][j];
                board[k][j] = 0;
                k--;
                moved = true;
            }
            if (k > 0 && board[k - 1][j] == board[k][j] && lastMerge != k - 1) {
                board[k - 1][j] *= 2;
                score += board[k - 1][j];
                board[k][j] = 0;
                lastMerge = k - 1;
                moved = true;
            }
        }
    }
    updateBestScore();
    return moved;
}

bool Game2048::moveDown() {
    bool moved = false;
    for (int j = 0; j < 4; ++j) {
        int lastMerge = 4;
        for (int i = 2; i >= 0; --i) {
            if (board[i][j] == 0) continue;
            int k = i;
            while (k < 3 && board[k + 1][j] == 0) {
                board[k + 1][j] = board[k][j];
                board[k][j] = 0;
                k++;
                moved = true;
            }
            if (k < 3 && board[k + 1][j] == board[k][j] && lastMerge != k + 1) {
                board[k + 1][j] *= 2;
                score += board[k + 1][j];
                board[k][j] = 0;
                lastMerge = k + 1;
                moved = true;
            }
        }
    }
    updateBestScore();
    return moved;
}

bool Game2048::canMove() const {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0) return true;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == board[i][j + 1]) return true;

    for (int j = 0; j < 4; ++j)
        for (int i = 0; i < 3; ++i)
            if (board[i][j] == board[i + 1][j]) return true;

    return false;
}

void Game2048::updateBestScore() {
    if (score > bestScore) {
        bestScore = score;
        QFile file("bestscore.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << bestScore;
            file.close();
        }
        emit bestScoreChanged(bestScore);
    }
}
