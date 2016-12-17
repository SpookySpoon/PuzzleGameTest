#include <QtTest/QtTest>
#include <QThread>
#include <QPair>
#include <QStringList>
#include <QPushButton>
#include <QMessageBox>
#include "gameengine.h"
#include "scorekeeper.h"
#include "congratulator.h"



class GameEngineTest : public QObject
{
    Q_OBJECT
private slots:
    void testNewGame();
    void testTryAgain();
    void testOnWin();
private:
    GameEngine gE;
};



void GameEngineTest::testNewGame()
{
    QPushButton pushButt;
    QObject::connect(&pushButt,SIGNAL(clicked()),&gE,SLOT(newGame()));
    QSignalSpy jBondNG(&gE,SIGNAL(callNewGame()));
    pushButt.click();
    QCOMPARE(gE.getRegime(),true);
    QCOMPARE(jBondNG.count(),1);
}

void GameEngineTest::testTryAgain()
{
    QPushButton pushButt;
    QObject::connect(&pushButt,SIGNAL(clicked()),&gE,SLOT(tryAgain()));
    QSignalSpy jBondTA(&gE,SIGNAL(callTryAgain()));
    pushButt.click();
    QCOMPARE(gE.getRegime(),false);
    QCOMPARE(jBondTA.count(),1);
}

void GameEngineTest::testOnWin()
{
    qRegisterMetaType<QPair<int,int>>();
    GameEngine* someGE = new GameEngine;
    QThread*  someThread= new QThread;

    ScoreKeeper* sKeeper = new ScoreKeeper;
    QObject::connect(someThread,SIGNAL(started()),sKeeper,SLOT(stopTracking()));
    QObject::connect(sKeeper,SIGNAL(reportScore(QPair<int,int>)),someGE,SLOT(onWin(QPair<int,int>)));
    someGE->moveToThread(someThread);
    sKeeper->moveToThread(someThread);
    someThread->start();
    QTest::qWait(1000);
    QSignalSpy jBondTA(sKeeper,SIGNAL(reportScore(QPair<int,int>)));

    QPair<int,int> stats(50,50);
    QList<Congratulator*> childStatement = someGE->findChildren<Congratulator*>(QString("Congratulator"));
    QCOMPARE(childStatement.count(),0);

    sKeeper->reportScore(stats);
    QList<Congratulator*> childStatement1 = someGE->findChildren<Congratulator*>(QString("Congratulator"));
    qDebug()<<"finish";

    QCOMPARE(jBondTA.count(),1);
    QCOMPARE(childStatement1.count(),1);
    someGE->deleteLater();
    someThread->deleteLater();

}

QTEST_MAIN(GameEngineTest)
#include "gameenginetest.moc"
