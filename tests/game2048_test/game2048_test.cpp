#include "game2048_test.hpp"
#include "game2048.hpp"
#include <QtTest>
#include <QSignalSpy>

void Game2048Test::initTestCase() {}
void Game2048Test::cleanupTestCase() {}

void Game2048Test::testInitialBoard() {
    Game2048 game;
    game.newGame();
    int count = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (game.getTile(i, j) != 0) count++;
    QVERIFY(count == 2);
    QCOMPARE(game.getScore(), 0);
}

void Game2048Test::testMoveLeft() {
    Game2048 game;
    game.placeTile(0, 1, 2);
    game.placeTile(0, 3, 4);
    QVERIFY(game.moveLeft());
    QCOMPARE(game.getTile(0, 0), 2);
    QCOMPARE(game.getTile(0, 1), 4);
    QCOMPARE(game.getTile(0, 2), 0);
    QCOMPARE(game.getTile(0, 3), 0);
}

void Game2048Test::testMergeLeft() {
    Game2048 game;
    game.placeTile(0, 0, 2);
    game.placeTile(0, 1, 2);
    QVERIFY(game.moveLeft());
    QCOMPARE(game.getTile(0, 0), 4);
    QCOMPARE(game.getTile(0, 1), 0);
    QCOMPARE(game.getScore(), 4);
}

void Game2048Test::testMoveRight() {
    Game2048 game;
    game.placeTile(0, 0, 2);
    game.placeTile(0, 2, 4);
    QVERIFY(game.moveRight());
    QCOMPARE(game.getTile(0, 3), 4);
    QCOMPARE(game.getTile(0, 2), 2);
}

void Game2048Test::testMoveUp() {
    Game2048 game;
    game.placeTile(2, 0, 2);
    game.placeTile(3, 0, 4);
    QVERIFY(game.moveUp());
    QCOMPARE(game.getTile(0, 0), 2);
    QCOMPARE(game.getTile(1, 0), 4);
}

void Game2048Test::testMoveDown() {
    Game2048 game;
    game.placeTile(0, 1, 2);
    game.placeTile(1, 1, 4);
    QVERIFY(game.moveDown());
    QCOMPARE(game.getTile(3, 1), 4);
    QCOMPARE(game.getTile(2, 1), 2);
}

void Game2048Test::testCanMoveEmpty() {
    Game2048 game;
    game.placeTile(0, 0, 2);
    QVERIFY(game.canMove());
}

void Game2048Test::testCanMoveMergable() {
    Game2048 game;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            game.placeTile(i, j, 2);
    QVERIFY(game.canMove());
}

void Game2048Test::testCannotMove() {
    Game2048 game;
    int v = 2;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            game.placeTile(i, j, v);
            v *= 3; // все разные → нет слияний
        }
    QVERIFY(!game.canMove());
}

void Game2048Test::testScoreOnMerge() {
    Game2048 game;
    game.placeTile(0, 0, 8);
    game.placeTile(0, 1, 8);
    game.moveLeft();
    QCOMPARE(game.getScore(), 16);
}

void Game2048Test::testBestScoreSignal() {
    Game2048 game;
    game.placeTile(0, 0, 1024);
    game.placeTile(0, 1, 1024);
    game.moveLeft();
    QCOMPARE(game.getBestScore(), 2048);
}
