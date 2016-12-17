#include <QtTest/QtTest>
#include <QObject>
#include <QMessageBox>
#include "staticfunctions.h"
#include "ui_puzzleform.h"



class StaticFuncTest : public QObject
{
    Q_OBJECT
private slots:
    void transPuzOrderTest();
    void transPuzOrderTest_data();
    void puzzleMoverTest();
    void puzzleMoverTest_data();
    void getWinningOrderTest();
    void shuffleList();
    //Дальше идут функции для связи с .txt файлом, где хранятся данные о лучших играх (лучшее время и меньшее количество ходов)
    void getScoreTest();
    void resetScoreTest();
    void resetScoreTest_data();
    void updateScoreTest();
    void updateScoreTest_data();
private:
    Ui::PuzzleForm someUiPuzForm;
};



void StaticFuncTest::puzzleMoverTest()
{
    QFETCH(QStringList,disposition);
    QFETCH(QString,button);
    QFETCH(QStringList,result);
    QFETCH(bool,resultFunc);
    bool res = StaticFunctions::puzzleMover(disposition,button);
    QCOMPARE(disposition,result);
    QCOMPARE(res,resultFunc);
}
void StaticFuncTest::puzzleMoverTest_data()
{
    QTest::addColumn<QStringList>( "disposition" );
    QTest::addColumn<QString>( "button" );
    QTest::addColumn<QStringList>( "result" );
    QTest::addColumn<bool>( "resultFunc" );

    QList<int> case1,case2,case3,case4,disposition;
    QList<QList<int>>caseList;
    QList<QStringList>caseListInString;

    disposition
        << 1<< 2<< 3<< 4
        << 5<< 6<< 0<< 8
        << 9<<10<<11<<12
        <<13<<14<<15<< 7;
    case1
        << 1<< 2<< 0<< 4
        << 5<< 6<< 3<< 8
        << 9<<10<<11<<12
        <<13<<14<<15<< 7;
    case2
        << 1<< 2<< 3<< 4
        << 5<< 6<< 8<< 0
        << 9<<10<<11<<12
        <<13<<14<<15<< 7;
    case3
        << 1<< 2<< 3<< 4
        << 5<< 0<< 6<< 8
        << 9<<10<<11<<12
        <<13<<14<<15<< 7;
    case4
        << 1<< 2<< 3<< 4
        << 5<< 6<<11<< 8
        << 9<<10<< 0<<12
        <<13<<14<<15<< 7;
    caseList<<case1<<case2<<case3<<case4<<disposition;

    for (auto lInt:caseList)
    {
        QStringList tempL;
        for(auto i: lInt)
        {
            if(i>0)
            {
                tempL.append(QString("pushButton_%1").arg(i));
            }
            else
            {
                tempL.append(QString(" "));
            }
        }
        caseListInString.append(tempL);
    }
    QTest::newRow("pushButton_3" )<<caseListInString.at(4)<<QString("pushButton_3" )<<caseListInString.at(0)<<true;
    QTest::newRow("pushButton_8" )<<caseListInString.at(4)<<QString("pushButton_8" )<<caseListInString.at(1)<<true;
    QTest::newRow("pushButton_6" )<<caseListInString.at(4)<<QString("pushButton_6" )<<caseListInString.at(2)<<true;
    QTest::newRow("pushButton_11")<<caseListInString.at(4)<<QString("pushButton_11")<<caseListInString.at(3)<<true;
    QTest::newRow("pushButton_1")<<caseListInString.at(4)<<QString("pushButton_1")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_2")<<caseListInString.at(4)<<QString("pushButton_2")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_4")<<caseListInString.at(4)<<QString("pushButton_4")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_5")<<caseListInString.at(4)<<QString("pushButton_5")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_9")<<caseListInString.at(4)<<QString("pushButton_9")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_10")<<caseListInString.at(4)<<QString("pushButton_10")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_12")<<caseListInString.at(4)<<QString("pushButton_12")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_13")<<caseListInString.at(4)<<QString("pushButton_13")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_14")<<caseListInString.at(4)<<QString("pushButton_14")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_15")<<caseListInString.at(4)<<QString("pushButton_15")<<caseListInString.at(4)<<false;
    QTest::newRow("pushButton_7")<<caseListInString.at(4)<<QString("pushButton_7")<<caseListInString.at(4)<<false;
}

void StaticFuncTest::transPuzOrderTest()
{
    QFETCH(QStringList,ButtonListRequest);
    QWidget someW;
    someUiPuzForm.setupUi(&someW);
    StaticFunctions::transPuzOrder(ButtonListRequest,&someUiPuzForm);
    int gridRows=someUiPuzForm.gridLayout->rowCount();
    int gridColumns=someUiPuzForm.gridLayout->columnCount();
    for (int row=0;row<gridRows;row++)
    {
        for (int column=0;column<gridColumns;column++)
        {
            int listIndex=row*gridColumns+column;
            QLayoutItem* button = someUiPuzForm.gridLayout->itemAtPosition(row,column);
            if(button)
            {
                QCOMPARE(ButtonListRequest.at(listIndex),button->widget()->objectName());
            }
            else
            {
                QCOMPARE(ButtonListRequest.at(listIndex),QString(" "));
            }
        }
    }
}
void StaticFuncTest::transPuzOrderTest_data()
{
    QTest::addColumn<QStringList>( "ButtonListRequest" );
    QList<int> case1,case2,case3,case4,case5;
    QList<QList<int>>caseList;
    case1<<0<<15<<14<<13<<12<<11<<10<<9<<8<<7<<6<<5<<4<<3<<2<<1;
    case2<<10<<5<<4<<3<<2<<1<<0<<9<<8<<7<<6<<15<<14<<13<<12<<11;
    case3<<0<<7<<6<<5<<4<<3<<15<<11<<10<<9<<8<<14<<13<<12<<2<<1;
    case4<<15<<14<<13<<12<<11<<4<<3<<2<<1<<10<<9<<8<<7<<6<<5<<0;
    case5<<6<<5<<4<<3<<0<<15<<14<<13<<12<<11<<10<<9<<8<<7<<2<<1;
    caseList<<case1<<case2<<case3<<case4<<case5;
    int caseNumb=1;
    for (auto lInt:caseList)
    {
        QStringList tempL;
        for(auto i: lInt)
        {
            if(i>0)
            {
                tempL.append(QString("pushButton_%1").arg(i));
            }
            else
            {
                tempL.append(QString(" "));
            }
        }
        QTest::newRow(tr("Case%1").arg(caseNumb).toLatin1().data())<<tempL;
        caseNumb++;
    }
}

void StaticFuncTest::shuffleList()
{
    QStringList buttonsBeforeShuffle;
    QStringList buttonsAfterShuffle;
    QList<int> case1;
    //Произвольный список с 15 кнопками и 1 пробелом
    case1<<6<<5<<4<<3<<15<<14<<13<<12<<11<<10<<9<<8<<7<<2<<1<<0;
    for(auto i: case1)
    {
        if(i>0)
        {
            buttonsBeforeShuffle.append(QString("pushButton_%1").arg(i));
        }
        else
        {
            buttonsBeforeShuffle.append(QString(" "));
        }
    }
    buttonsAfterShuffle=buttonsBeforeShuffle;
    StaticFunctions::shuffleList(buttonsAfterShuffle);
    //Проверяем, что разные списки после прогона функции
    QVERIFY(buttonsAfterShuffle!=buttonsBeforeShuffle);
    //Проверяем, что пробел стоит в конце
    QCOMPARE(buttonsAfterShuffle.last(),QString(" "));
    //Ниже соритруем и сверяем два списка, чтобы убедиться, что все кнопки на месте (в исходном списке все на месте)
    std::sort(buttonsAfterShuffle.begin(),buttonsAfterShuffle.end());
    std::sort(buttonsBeforeShuffle.begin(),buttonsBeforeShuffle.end());
    QCOMPARE(buttonsAfterShuffle,buttonsBeforeShuffle);
}

void StaticFuncTest::getWinningOrderTest()
{
    QStringList wO;
    for (int i=1;i<=15;i++)
    {
        wO<<QString("pushButton_%1").arg(i);
    }
    wO<<" ";
    QCOMPARE(wO,StaticFunctions::getWinningOrder());
}

void StaticFuncTest::getScoreTest()
{
//Функция должна возвращать список из 5 целых чисел (лучшее время, меньшее количество ходов, лучшие время и ходы в совокупностиб количество игр).
    QList<int> score = StaticFunctions::getScore();
    QCOMPARE(score.count(),5);
}

void StaticFuncTest::resetScoreTest()
{
//Функция для удаления данных из .txt файла и записи туда игровой статистики, указанной в аргументах
//Проверяем корректность протестированной ранее функцией getScore()
//Поскольку вызов данной функции осуществляется самой программой и нет вероятности, что пользователь введет не те данные, в ней нет проверки на нереальные числа (отрицательные)
//Поэтомы ситуации с отрицательными параметрами не тестируются
    QFETCH(QList<int>,input);
    QFETCH(QList<int>,result);
    StaticFunctions::resetScore(input.first(),input.last());
    QCOMPARE(result,StaticFunctions::getScore());
}

void StaticFuncTest::resetScoreTest_data()
{
    QTest::addColumn<QList<int>>( "input" );
    QTest::addColumn<QList<int>>( "result" );
    QList<int>case1,case2,case3,case4,result1,result2,result3,result4;
    case1<<10<<20;
    case2<<20<<10;
    case3<<0<<0;
    case4<<15<<15;
    result1<<10<<20<<10<<20<<1;
    result2<<20<<10<<20<<10<<1;
    result3<<0<<0<<0<<0<<1;
    result4<<15<<15<<15<<15<<1;
    QTest::newRow("input1")<<case1<<result1;
    QTest::newRow("input2")<<case2<<result2;
    QTest::newRow("input3")<<case3<<result3;
    QTest::newRow("input4")<<case4<<result4;
}

void StaticFuncTest::updateScoreTest()
{
//Это функция получает статистику игрока (время и ходы), сравнивает её с рекордами и при необходимости меняет .txt файл.
//Ниже проверяется логика сравнения. Мы запускаем updateScore(), а потом запрашиваем данные через getScore() и сравниваем с ожидаемыми данными
//Тест начинается с того, что данные устанавливаются через resetScore() на 50 секунд и 50 ходов. Дальше проверются ситуации, когда данные должны меняться и нет.
//Также эта функция прибавляет количество пройденных игр, так что последний аргумент должен в наших ситуациях должен быть равен двум (resetScore - данные за первую игру, update - вторая игра)
    StaticFunctions::resetScore(50,50);
    QFETCH(QList<int>,input);
    QFETCH(QList<int>,result);
    StaticFunctions::updateScore(input.first(),input.last());
    QCOMPARE(StaticFunctions::getScore(),result);
}

void StaticFuncTest::updateScoreTest_data()
{
    QTest::addColumn<QList<int>>( "input" );
    QTest::addColumn<QList<int>>( "result" );
    QList<int>case1,case2,case3,case4,result1,result2,result3,result4;
    case1<<60<<60;
    case2<<40<<40;
    case3<<40<<60;
    case4<<60<<40;
    result1<<50<<50<<50<<50<<2;
    result2<<40<<40<<40<<40<<2;
    result3<<40<<50<<50<<50<<2;
    result4<<50<<40<<50<<50<<2;
    QTest::newRow("input1")<<case1<<result1;
    QTest::newRow("input2")<<case2<<result2;
    QTest::newRow("input3")<<case3<<result3;
    QTest::newRow("input4")<<case4<<result4;

}


QTEST_MAIN(StaticFuncTest)
#include "staticfunctest.moc"
