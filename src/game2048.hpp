#include <QObject>

class Game2048 : public QObject {
    Q_OBJECT

public:
    explicit Game2048(QObject *parent = nullptr);

    void newGame();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool canMove() const;

    int getScore() const { return score; }
    int getBestScore() const { return bestScore; }
    int getTile(int row, int col) const { return board[row][col]; }

    void addRandomTile();
    void updateBestScore();

    int board[4][4] = {};
    int score = 0;
    int bestScore = 0;

    void placeTile(int row, int col, int value) { board[row][col] = value; }

};
