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
    void testOnNewGame();
//    void testOnRestart();
private:
    PuzzleManager puzMan;
};

void PuzzleManagerTest::testOnPushedButtons()
{
//При нажатии сегмента пазла, он должен прыгнуть в пустую ячейку, если она есть рядом, либо остаться на месте, если её рядом нет.
//Сначала проверяется, что те кнопки, которые должны оставаться на месте, остаются на месте.
//Потом проверяется, что те кнопки, которые должны двигаться, двигаются правильно (для них правильно рассчитывается позиция).
    QPushButton pushButt;
    QObject::connect(&pushButt,SIGNAL(clicked()),&puzMan,SLOT(onPushedButton()));
    QSignalSpy jBond(&puzMan,SIGNAL(assignedOrder(QVariant)));
    QFETCH(QString,buttonName);
    QFETCH(int,signalCount);
    QFETCH(QStringList,signalContent);
//Механизм расчета позиции куска пазла основан на том, что PuzzleManager получает имя кнопки через QObject::sender().
//Затем, имея у себя QStringList имен кнопок в текущей последовательности, PuzzleManager при необходимости делает в своём QStringList перестановки и шлёт его UI форме (puzzleform).
//А дальше puzzleform настраивает раскладку кнопок согласно полученному QStringList, в котором имена кнопок расположены в правильном порядке.

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


void PuzzleManagerTest::testOnNewGame()
{
//Когда начинается новая игра, PuzzleManager отвечает только за перемешивание кнопок случайным образом.
//Надо проверить, что когда срабатывает слот "OnNewGame()", новый порядок кнопок отвечает следующим требованиям:
    //1) Он отличается от порядка кнопок в начале текущей игры
    //2) В нём отсутствуют повторяющиеся значения (представлены все кнопки с 1 по 15)
    //3) Последний элемент списка содержит пробел (символ пустой ячейки)
    //4) Количество элементов QStringList = 16
//Для этого выполняются следующие действия:

    //1) Создаём упорядоченный список initialButtons с пробелом в конце. Этот список представляет исходное состояние кнопок при создании PuzzleManager.
        //Поскольку в контексте тестирования слот "OnNewGame()" ни разу не запускался, для нас эта последовательность будет отправной точкой тестирования "OnNewGame()".
    //2) Для проверки требований 2 и 4 создаём список "benchmark", являющийся копией списка "initialButtons".
    //3) Создаём кнопку и связываем её сигнал со слотом "OnNewGame()";
    //4) Создаём QSignalSpy и ловим QStringList, который наш PuzzleManager передаёт UI для отображения.
    //5) Сравниваем полученный QStringList с initialButtons в разрезе требования 1. Поскольку в нормальной ситуации тут должен быть фейл, ставим макрос QEXPECT_FAIL, чтобы он игнорил ошибку.
    //6) Чтобы убедиться, что в новом списке все кнопки уникальны и их 16 штук, мы сортируем прочитанный QSignalSpy список и список "benchmark" (приводим к одному состоянию) и сравниваем их.
    //7) Требование 3 - проверяем последный символ прочитанного QSignalSpy списка.
    //8) По мере прохождения теста сохраняем сигналенный список как "initialButtons" и повторяем проверку n раз.

    QStringList initialButtons;
    for (int i=1;i<=15;i++)
    {
        initialButtons<<QString("pushButton_%1").arg(i);
    }
    initialButtons<<QString(" ");


    QStringList benchmark=initialButtons;
    std::sort(benchmark.begin(),benchmark.end());
    for (int i=0;i<10;i++)
    {
        QPushButton pushButt;
        QObject::connect(&pushButt,SIGNAL(clicked()),&puzMan,SLOT(onNewGame()));
        QSignalSpy jBond(&puzMan,SIGNAL(assignedOrder(QVariant)));
        pushButt.click();
        QVariant someVar=jBond.first().first();
        QStringList someList=someVar.toStringList();
        QStringList someListSorted=someList;
        QEXPECT_FAIL("", "New button order must differ from the initial one",Continue);
        QCOMPARE(someList,initialButtons);                      //Требование №1
        std::sort(someListSorted.begin(),someListSorted.end());
        QCOMPARE(someListSorted,benchmark);                     //Требования №2 и 4
        QCOMPARE(someList.last(),QString(" "));                 //Требование №3
        initialButtons=someList;
    }
}


QTEST_MAIN(PuzzleManagerTest)
#include "puzzlemanagertest.moc"
