#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include "game2048.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void newGame();
    void updateUI();

private:
    Game2048 *game;
    QWidget *central;
    QGridLayout *grid;
    QLabel *tiles[4][4];
};
