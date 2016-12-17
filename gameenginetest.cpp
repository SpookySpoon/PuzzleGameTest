#include <QMessageBox>
#include <QtTest/QtTest>
#include <QThread>
#include <QTimer>
#include <QPair>
#include <QStringList>
#include <QPushButton>
#include "gameengine.h"
#include "scorekeeper.h"
#include "congratulator.h"
#include "ui_puzzleform.h"


class GameEngineTest : public QObject
{
    Q_OBJECT
private slots:
    void testNewGame();
    void testTryAgain();
    void testOnWOn();//Вот этот засранец, я с ним долго просидел и в итоге подпёр костылем. См. вопрос в самом слоте.
    void inThread();
private:
    GameEngine gE;
    QThread myThread;
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

void GameEngineTest::testOnWOn()
{
    //Прежде чем задать вопрос обрисую ситуацию
    //Всё что делает этот слот, это создание класса Congratulator, управляющего окном результатов игры.
    //Этот класс открывает окно в диалоговом режиме, которое блокирует главный тред.
    //ЧТобы проверить, что этот слот работает корректно и Congratulator запустился,
        //я решил воспользоваться поиском детей класса GameEngine с определенным именем, которое в этом слоте присваивается классу Congratulator
    //Но проблема была в том, что пока Congratulator существует, я не могу посчитать детей, а когда мы закрываем окно, созданное классом Congratulator,
        // детей с именем, присвоенным Congratulator мы уже найти не можем, потмоучто их нет.
    //Поэтому я запустил слот inThread() в новом потоке, где я ищу детей класса GameEngine, пока открыто диалоговое окно Congratulator.

    //Теперь вопрос - у меня поток со слотом inThread() запускается до того, как я активирую слот onWin(QPair<int,int>) класса GameEngine.
    //Следовательно инструкция создать Congratulator идет после того, как я отпустил инструкцию узнать количество детей с именем "Congratulator".
    //Тем не менее, моим методом программа успевает создать Congratulator до того, как слот inThread() начнет искать детей и у меня тест проходит успешно.
    //ВОпрос - при таком раскладе может ли быть ситуация, когда inThread() выполнит инструкции в своём потоке раньше, чем в главном потоке будет создан Congratulator?
    //Тоесть может ли из за этого не сработать тест?

    int cNum=gE.findChildren<Congratulator*>(QString("Congratulator")).count();
    QCOMPARE(cNum,0);
    moveToThread(&myThread);
    connect(&myThread, SIGNAL(started()), this, SLOT(inThread()));
    myThread.start();
    QPair<int,int> opAr(50,50);
    gE.onWin(opAr);
    myThread.exit();
}

void GameEngineTest::inThread()
{
//    QThread::currentThread()->wait(1000);
    int cNum=gE.findChildren<Congratulator*>(QString("Congratulator")).count();
    QCOMPARE(cNum,1);

}

QTEST_MAIN(GameEngineTest)
#include "gameenginetest.moc"
