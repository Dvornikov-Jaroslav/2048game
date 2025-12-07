#include "mainwindow.hpp"
#include <QMenuBar>
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), game(new Game2048(this))
{
    central = new QWidget(this);
    setCentralWidget(central);
    grid = new QGridLayout(central);
    grid->setSpacing(8);
    grid->setContentsMargins(10, 10, 10, 10);

    QFont font;
    font.setPointSize(18);
    font.setBold(true);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            tiles[i][j] = new QLabel(" ", this);
            tiles[i][j]->setAlignment(Qt::AlignCenter);
            tiles[i][j]->setFixedSize(80, 80);
            tiles[i][j]->setFont(font);
            tiles[i][j]->setStyleSheet("background-color: #CDC1B4; border-radius: 10px;");
            grid->addWidget(tiles[i][j], i, j);
        }

    QMenu *gameMenu = menuBar()->addMenu("Игра");
    QAction *newAction = new QAction("Новая игра", this);
    QAction *exitAction = new QAction("Выход", this);
    connect(newAction, &QAction::triggered, this, &MainWindow::newGame);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    gameMenu->addAction(newAction);
    gameMenu->addAction(exitAction);

    newGame();
}

void MainWindow::newGame() {
    game->newGame();
    updateUI();
}

void MainWindow::updateUI() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int v = game->getTile(i, j);
            tiles[i][j]->setText(v == 0 ? "" : QString::number(v));
            QString color;
            switch (v) {
                case 0: color = "#CDC1B4"; break;
                case 2: color = "#EEE4DA"; break;
                case 4: color = "#EDE0C8"; break;
                case 8: color = "#F2B179"; break;
                case 16: color = "#F59563"; break;
                case 32: color = "#F67C5F"; break;
                case 64: color = "#F65E3B"; break;
                case 128: color = "#EDCF72"; break;
                case 256: color = "#EDCC61"; break;
                case 512: color = "#EDC850"; break;
                case 1024: color = "#EDC53F"; break;
                case 2048: color = "#EDC22E"; break;
                default: color = "#3C3A32";
            }
            tiles[i][j]->setStyleSheet(QString(
                "background-color: %1; border-radius: 10px; font-weight: bold; color: black;").arg(color));
            if (v >= 16) tiles[i][j]->setStyleSheet(tiles[i][j]->styleSheet() + " color: white;");
        }
    }
    setWindowTitle(QString("2048 — Счёт: %1 | Рекорд: %2")
        .arg(game->getScore()).arg(game->getBestScore()));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    bool moved = false;
    switch (event->key()) {
    case Qt::Key_Left:  moved = game->moveLeft(); break;
    case Qt::Key_Right: moved = game->moveRight(); break;
    case Qt::Key_Up:    moved = game->moveUp(); break;
    case Qt::Key_Down:  moved = game->moveDown(); break;
    default: return;
    }

    if (moved) {
        game->addRandomTile(); // вызываем явно после хода
        updateUI();
        if (!game->canMove()) {
            QMessageBox::information(this, "Игра окончена",
                QString("Ваш счёт: %1").arg(game->getScore()));
        }
    }
}
