#include <QtTest/QtTest>
#include <QMessageBox>
#include <QList>
#include <QPushButton>
#include <QDebug>
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
    QSignalSpy jBonda(&pushButt,SIGNAL(clicked()));
    QFETCH(QString,buttonName);
    QFETCH(int,signalCount);
    QFETCH(QStringList,signalContent);
    if(pushButt.objectName()!=buttonName)
    {
        pushButt.setObjectName(buttonName);
        pushButt.click();
    }

    if(signalCount)
    {
        QCOMPARE(jBond.count(),1);
        QVariant someVar=jBond.first().first();
        QStringList someList=someVar.toStringList();
        QCOMPARE(someList,signalContent);
//                QMessageBox opa;
//                opa.setText(QString("Fetched FW is: %1, and signaled FW is: %2.").arg(someList.first()).arg(signalContent.first()));
//                opa.exec();
    }
    else
    {
        QCOMPARE(jBond.count(),0);
    }

}

void PuzzleManagerTest::testOnPushedButtons_data()
{
//Исходный порядок кнопок "initialButtonOrder". Такой порядок задаётся в конструкторе PuzzleManagerTest
//    QList<QString> initialButtonOrder;
//    for (int i=1;i<=15;i++)
//    {
//        initialButtonOrder<<QString("pushButton_%1").arg(i);
//    }
//    initialButtonOrder<<QString(" ");
//passiveButtons - кнопки, нажатие которых ничего не меняет (все, кроме №12 и №15).
//    QList<QString> passiveButtons=initialButtonOrder;
//    passiveButtons.removeLast();
//    passiveButtons.removeLast();
//    passiveButtons.removeAt(11);

    QTest::addColumn<QString>( "buttonName" );
    QTest::addColumn<int>( "signalCount" );
    QTest::addColumn<QStringList>( "signalContent" );

//    for(auto i:passiveButtons)
//    {
//        QList<QString> emptyList;
//        QString iter=i;
//        QTest::newRow(iter.toLatin1().data()) << i << 0 << emptyList;
//    }
//Дальше в таблицу тестирвоания добавляются списки кнопок, если двигать кнопки по спирали против часовой стрелки.
//Сначала делал церез цикл (задал порядок кнопок и потом делал замену пробелов), но это в какой-то степени повоторение кода в тестируемой модели.
//Если тестируемый код упадет, то в самом тестировании он наверняка тоже упадет, так что решил вручную вписать
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
