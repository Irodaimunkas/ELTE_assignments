#include <QString>
#include <QtTest>
#include "blackholemodel.h"
#include "dataaccessmock.h"

class BlackHoleTest : public QObject
{
    Q_OBJECT

private:
    blackHoleModel *_model;
    dataAccess *_dataAccessMock;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testFindthenMoveShips();
    void testShipDirChange();
    void testSaveGame();
    void testLoadGame();
};

void BlackHoleTest::initTestCase()
{
    _dataAccessMock = new dataAccessMock();
    _model = new blackHoleModel(_dataAccessMock);
}

void BlackHoleTest::cleanupTestCase(){
    delete _dataAccessMock;
    delete _model;
}

void BlackHoleTest::testNewGame(){
    _model->newGame(7);
    QCOMPARE(_model->getFieldType(0,0), RED);
    QCOMPARE(_model->getFieldType(1,1), RED);
    QCOMPARE(_model->getFieldType(1,5), RED);
    QCOMPARE(_model->getFieldType(0,6), RED);

    QCOMPARE(_model->getFieldType(6,0), BLUE);
    QCOMPARE(_model->getFieldType(5,1), BLUE);
    QCOMPARE(_model->getFieldType(5,5), BLUE);
    QCOMPARE(_model->getFieldType(6,6), BLUE);

    QCOMPARE(_model->getFieldType(3,3), B_HOLE);

    QCOMPARE(_model->getMapSize(), 7);
    QCOMPARE(_model->getPlayer(), PLAYER_ONE);
}

void BlackHoleTest::testFindthenMoveShips(){
    _model->newGame(5);
    _model->setFieldDir(0, 0, DOWN);
    _model->findThenMoveShips();

    QCOMPARE(_model->getFieldType(3, 0), RED);
}

void BlackHoleTest::testShipDirChange(){
    _model->newGame(5);
    QCOMPARE(_model->getFieldDir(0,0), NO_DIR);
    _model->shipDirChange(0,0);
    QCOMPARE(_model->getFieldDir(0,0), UP);
    _model->shipDirChange(0,0);
    QCOMPARE(_model->getFieldDir(0,0), RIGHT);
}

void BlackHoleTest::testSaveGame(){
    _model->newGame(7);
    _model->saveGame();
}

void BlackHoleTest::testLoadGame(){
    _model->loadGame();
}

QTEST_APPLESS_MAIN(BlackHoleTest)

#include "blackholetest.moc"
