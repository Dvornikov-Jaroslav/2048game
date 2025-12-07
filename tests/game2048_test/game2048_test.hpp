#include <QObject>

class Game2048Test : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testInitialBoard();
    void testMoveLeft();
    void testMergeLeft();
    void testMoveRight();
    void testMoveUp();
    void testMoveDown();
    void testCanMoveEmpty();
    void testCanMoveMergable();
    void testCannotMove();
    void testScoreOnMerge();
    void testBestScoreSignal();
};
