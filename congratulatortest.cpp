//#include <QApplication>
//#include <QtTest/QtTest>
//#include <QPair>
//#include "congratulator.h"

//class CongratulatorTest : public QObject
//{
//    Q_OBJECT

//private slots:
//    void testCongratulatorNewGame();
//    void testCongratulatorTryAgain();
//};

//void CongratulatorTest::testCongratulatorNewGame()
//{
//    QPair<int,int> inputPair(5,5);
//    qRegisterMetaType<QPair<int,int>>("Pair");
//    bool gameRegime=true;
//    Congratulator* testCon= new Congratulator(inputPair, gameRegime);
//    QSignalSpy jB_NewGame(testCon,SIGNAL(initScoreHandler(QPair<int,int>)));
//    QSignalSpy jB_TryAgain(testCon,SIGNAL(initScoreHandlerNoRecord(QPair<int,int>)));
//    testCon->setUpCongratulator();
//    testCon->deleteLater();
//    QCOMPARE (jB_NewGame.count(),1);
//    QCOMPARE (jB_TryAgain.count(),0);

//}

//void CongratulatorTest::testCongratulatorTryAgain()
//{
//    QPair<int,int> inputPair(5,5);
//    qRegisterMetaType<QPair<int,int>>("Pair");
//    bool gameRegime=false;
//    Congratulator* testCon= new Congratulator(inputPair, gameRegime);
//    QSignalSpy jB_NewGame(testCon,SIGNAL(initScoreHandler(QPair<int,int>)));
//    QSignalSpy jB_TryAgain(testCon,SIGNAL(initScoreHandlerNoRecord(QPair<int,int>)));
//    testCon->setUpCongratulator();
//    testCon->deleteLater();
//    QCOMPARE (jB_NewGame.count(),0);
//    QCOMPARE (jB_TryAgain.count(),1);

//}


//QTEST_MAIN(CongratulatorTest)
//#include "congratulatortest.moc"
