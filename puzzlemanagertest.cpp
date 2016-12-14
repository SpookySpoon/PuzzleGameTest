#include <QtTest/QtTest>
#include <QStringList>
#include <QPushButton>
#include "puzzlemanager.h"


class PuzzleManagerTest : public QObject
{
    Q_OBJECT
private slots:
    void testOnPushedButtons();
    void testOnPushedButtons_data();
private:
    PuzzleManager puzMan;
};

void PuzzleManagerTest::testOnPushedButtons()
{
    QPushButton pushButt;
    QObject::connect(&pushButt,SIGNAL(clicked()),&puzMan,SLOT(onPushedButton()));
    QSignalSpy jBond(&puzMan,SIGNAL(assignedOrder(QVariant)));
    QFETCH(QString,buttonName);
    QFETCH(int,signalCount);
    QFETCH(QStringList,signalContent);
//Механизм расчета позиции куска пазла таков основан на том, что PuzzleManager получает имя объекта -QObject::sender().
//Затем, имея у себя QStringList имен кнопок в нужной последовательности, PuzzleManager при необходимости делает в своём QStringList и шлёт UI форме (puzzleform).
//А дальше puzzleform настраивает раскладку кнопок согласно полученному QStringList.

//Это я всё к тому, что в нижней строчке меняется имя QObject::sender()-а (в нашем случае - кнопки), чтобы спровоцировать разное поведение PuzzleManager.

    pushButt.setObjectName(buttonName);
    pushButt.click();
//Дальше, собственно, сам тест.
    if(signalCount)
    {
        QCOMPARE(jBond.count(),1);
        QVariant someVar=jBond.first().first();
        QStringList someList=someVar.toStringList();
        QCOMPARE(someList,signalContent);
    }
    else
    {
        QCOMPARE(jBond.count(),0);
    }
}

void PuzzleManagerTest::testOnPushedButtons_data()
{
//Параметры
    QTest::addColumn<QString>( "buttonName" );
    QTest::addColumn<int>( "signalCount" );
    QTest::addColumn<QStringList>( "signalContent" );


//Изначально в конструкторе PuzzleManager создаётся упорядоченный список с кнопками (такой порядок надо собрать).
//Зная это, мы можем проверить поведение PuzzleManager в ответ на запрос разных кнопок и убедиться, что он их правильно сортирует.
//Сначала добавляются строки с кнопками, никак не меняющими раскладку пазла (все, кроме кнопок №12 и №15).
    QStringList passiveButtons;
    for (int i=1;i<=14;i++)
    {
        passiveButtons<<QString("pushButton_%1").arg(i);
    }
    passiveButtons.removeAt(11); //удаляем кнопку №12
    for(auto i:passiveButtons)
    {
        QStringList emptyList;
        QTest::newRow(i.toLatin1().data()) << i << 0 << emptyList;
    }
//Дальше в таблицу тестирвоания добавляются списки кнопок, которые должен сигналить PuzzleManager,
//если нажимать кнопки паззла по спирали против часовой стрелки, начиная с №15 - й.
////P.S. Сначала делал церез цикл (задал порядок кнопок и потом делал замену пробелов), но это в какой-то степени повоторение кода в тестируемой модели.
////Если тестируемый код упадет, то в самом тестировании он наверняка тоже упадет, так что решил вручную вписать
    QStringList onPushButton_15;
    onPushButton_15<<QString("pushButton_1")<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString("pushButton_5")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_9")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_13")<<QString("pushButton_14")<<QString(" ")<<QString("pushButton_15");
    QTest::newRow("onPushButton_15") << QString("pushButton_15") <<1<< onPushButton_15;
    QStringList onPushButton_14;
    onPushButton_14<<QString("pushButton_1")<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString("pushButton_5")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_9")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_13")<<QString(" ")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_14") << QString("pushButton_14") <<1<< onPushButton_14;
    QStringList onPushButton_13;
    onPushButton_13<<QString("pushButton_1")<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString("pushButton_5")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_9")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString(" ")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_13") << QString("pushButton_13") <<1<< onPushButton_13;
    QStringList onPushButton_9;
    onPushButton_9<<QString("pushButton_1")<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString("pushButton_5")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString(" ")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_9") << QString("pushButton_9") <<1<< onPushButton_9;
    QStringList onPushButton_5;
    onPushButton_5<<QString("pushButton_1")<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString(" ")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_5") << QString("pushButton_5") <<1<< onPushButton_5;
    QStringList onPushButton_1;
    onPushButton_1<<QString(" ")<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_1") << QString("pushButton_1") <<1<< onPushButton_1;
    QStringList onPushButton_2;
    onPushButton_2<<QString("pushButton_2")<<QString(" ")<<QString("pushButton_3")<<QString("pushButton_4")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_2") << QString("pushButton_2") <<1<< onPushButton_2;
    QStringList onPushButton_3;
    onPushButton_3<<QString("pushButton_2")<<QString("pushButton_3")<<QString(" ")<<QString("pushButton_4")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_3") << QString("pushButton_3") <<1<< onPushButton_3;
    QStringList onPushButton_4;
    onPushButton_4<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString(" ")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_8")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_4") << QString("pushButton_4") <<1<< onPushButton_4;
    QStringList onPushButton_8;
    onPushButton_8<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString("pushButton_8")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString(" ")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString("pushButton_12")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_8") << QString("pushButton_8") <<1<< onPushButton_8;
    QStringList onPushButton_12;
    onPushButton_12<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString("pushButton_8")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_12")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString("pushButton_11")<<QString(" ")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_12") << QString("pushButton_12") <<1<< onPushButton_12;
    QStringList onPushButton_11;
    onPushButton_11<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString("pushButton_8")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_12")
               <<QString("pushButton_5")<<QString("pushButton_10")<<QString(" ")<<QString("pushButton_11")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_11") << QString("pushButton_11") <<1<< onPushButton_11;
    QStringList onPushButton_10;
    onPushButton_10<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString("pushButton_8")
                <<QString("pushButton_1")<<QString("pushButton_6")<<QString("pushButton_7")<<QString("pushButton_12")
               <<QString("pushButton_5")<<QString(" ")<<QString("pushButton_10")<<QString("pushButton_11")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_10") << QString("pushButton_10") <<1<< onPushButton_10;
    QStringList onPushButton_6;
    onPushButton_6<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString("pushButton_8")
                <<QString("pushButton_1")<<QString(" ")<<QString("pushButton_7")<<QString("pushButton_12")
               <<QString("pushButton_5")<<QString("pushButton_6")<<QString("pushButton_10")<<QString("pushButton_11")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_6") << QString("pushButton_6") <<1<< onPushButton_6;
    QStringList onPushButton_7;
    onPushButton_7<<QString("pushButton_2")<<QString("pushButton_3")<<QString("pushButton_4")<<QString("pushButton_8")
                <<QString("pushButton_1")<<QString("pushButton_7")<<QString(" ")<<QString("pushButton_12")
               <<QString("pushButton_5")<<QString("pushButton_6")<<QString("pushButton_10")<<QString("pushButton_11")
              <<QString("pushButton_9")<<QString("pushButton_13")<<QString("pushButton_14")<<QString("pushButton_15");
    QTest::newRow("onPushButton_7") << QString("pushButton_7") <<1<< onPushButton_7;
}


QTEST_MAIN(PuzzleManagerTest)
#include "puzzlemanagertest.moc"
