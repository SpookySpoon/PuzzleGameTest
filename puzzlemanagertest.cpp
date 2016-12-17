#include <QtTest/QtTest>
#include <QStringList>
#include <QPushButton>
#include "puzzlemanager.h"
#include "ui_puzzleform.h"


class PuzzleManagerTest : public QObject
{
    Q_OBJECT
private slots:
    void testOnPushedButtons();
    void testOnNewGame();
    void testOnRestart();
//    void testOnCheat(); //"Это не тестил так, как это незаконно (просто чит для отладки) =Р
private:
//    Ui::PuzzleForm someUiPuzForm;
//    PuzzleManager puzMan(someUiPuzForm);
    QStringList initialButtons();
};

void PuzzleManagerTest::testOnPushedButtons()
{
//Сейчас (после того, как я переписал паззл) в этом слоте все рассчеты делаются статическими ф-ми и сигналов нет никаких.
//Есть только UI класс в аргументе, который и меняется. Так что все изменения отражаются в раскладке UI кнопок. Их и проверяем.
//Поскольку в данном слотеиспользуются оттестированные функции класса StaticFunctions, мы проверяем всего один сценарий, чтобы убедиться,
    //что UI в принципе реагирует.
//Для этого мы создаём UI класс, проверяем, что там правильный исходный порядок (по возрастанию), двигаем 15 кнопку, проверяем, что 15 кнопка двинулась.

    Ui::PuzzleForm someUiPuzFormTest;
    QWidget tempW;
    someUiPuzFormTest.setupUi(&tempW);
    PuzzleManager puzManTest(&someUiPuzFormTest);
    QStringList initialButtonsOrder = initialButtons();
    int gridRows=someUiPuzFormTest.gridLayout->rowCount();
    int gridColumns=someUiPuzFormTest.gridLayout->columnCount();
 //Проверяем исходный порядок
    for (int row=0;row<gridRows;row++)
    {
        for (int column=0;column<gridColumns;column++)
        {
            int listIndex=row*gridColumns+column;
            QLayoutItem* button = someUiPuzFormTest.gridLayout->itemAtPosition(row,column);
            if(button)
            {
                QCOMPARE(initialButtonsOrder.at(listIndex),button->widget()->objectName());
            }
            else
            {
                QCOMPARE(initialButtonsOrder.at(listIndex),QString(" "));
            }
        }
    }
//Создаём связь и двигаем кнопку
    QPushButton* opaButt=someUiPuzFormTest.pushButton_15;
    QObject::connect(opaButt,SIGNAL(clicked()),&puzManTest,SLOT(onPushedButton()));
    opaButt->click();
    QLayoutItem* lA=someUiPuzFormTest.gridLayout->itemAtPosition(gridRows-1,gridColumns-1);
    QVERIFY(lA!=0);
    QString pButName=lA->widget()->objectName();

    //Проверяем где кнопка
    QCOMPARE(pButName,QString("pushButton_15"));
}


void PuzzleManagerTest::testOnNewGame()
{
//Когда начинается новая игра, PuzzleManager отвечает только за перемешивание кнопок случайным образом.
//В этом слоте работает функция StaticFunctions::shuffleList, которая уже протещена.
//Поэтому тут тоже тестируется минимум.
//Надо проверить, что когда срабатывает слот "OnNewGame()", новый порядок кнопок отвечает следующим требованиям:
    //1) Он отличается от порядка кнопок в начале текущей игры
    //2) В нём отсутствуют повторяющиеся значения (представлены все кнопки с 1 по 15)
    //3) Последний элемент списка содержит пробел (символ пустой ячейки)
    //4) Количество элементов QStringList = 16
//Для этого выполняются следующие действия:
    //1) Создаётся новый UI файл. Корректность исходного расположения кнопок проверялась в тесте testOnPushedButtons(). Так что здесь это не првоеряем.
    //2) Создаём PuzzleManager и связываем его слот onNewGame() с кнопкой.
    //3) Нажимаем кнопку, составляем список расположения кнопок
    //4) Проверяем, что получившийся порядок кнопок отличается от исходного.
    //5) Проверяем, что в списке представлены все 15 кнопок, что последняя кнопка пустая.
//1)
    QStringList initialButtonsOrder = initialButtons();
    Ui::PuzzleForm someUiPuzFormTest;
    QWidget tempW;
    someUiPuzFormTest.setupUi(&tempW);
//2)
    PuzzleManager puzManTest(&someUiPuzFormTest);
    QPushButton* opaButt=someUiPuzFormTest.buttonShuffle;
    QObject::connect(opaButt,SIGNAL(clicked()),&puzManTest,SLOT(onNewGame()));
//3)
    opaButt->click();

    QStringList NewOrder;
    int gridRows=someUiPuzFormTest.gridLayout->rowCount();
    int gridColumns=someUiPuzFormTest.gridLayout->columnCount();

    for (int row=0;row<gridRows;row++)
    {
        for (int column=0;column<gridColumns;column++)
        {
            QLayoutItem* button = someUiPuzFormTest.gridLayout->itemAtPosition(row,column);
            if(button)
            {
                NewOrder.append(button->widget()->objectName());
            }
            else
            {
                NewOrder.append(QString(" "));
            }
        }
    }
//4)
    QVERIFY(initialButtonsOrder!=NewOrder);
//5)
    QCOMPARE(NewOrder.last(),QString(" "));
    std::sort(NewOrder.begin(),NewOrder.end());
    std::sort(initialButtonsOrder.begin(),initialButtonsOrder.end());
    QCOMPARE(initialButtonsOrder,NewOrder);
}




void PuzzleManagerTest::testOnRestart()
{
//Тут просто паззл откатывается к исходной последователььности фрагментов (имен кнопок в списке, который задаётся сразу после слота "OnNewGame()".
//Следовательно проверить надо только то, что понажимав какие-то кнопки, если мы запустим "OnRestart()", то UI вернет кнопки в исходное положение
//Для проверки этого, мы делаем следующее:
    //1) Создаём новый UI класс
    //2) Нажимаем 15 кнопку
    //3) Проверяем, что она сдвинулась
    //4) Активируем OnRestart()
    //5) Проверяем, что все кнопки вернулись на место
//1)
    QStringList initialButtonsOrder = initialButtons();
    Ui::PuzzleForm someUiPuzFormTest;
    QWidget tempW;
    someUiPuzFormTest.setupUi(&tempW);
    PuzzleManager puzManTest(&someUiPuzFormTest);
    QPushButton opaButt;
    opaButt.setObjectName(QString("pushButton_15"));
    QObject::connect(&opaButt,SIGNAL(clicked()),&puzManTest,SLOT(onPushedButton()));
//2)
    opaButt.click();
//3)
    QLayoutItem* button = someUiPuzFormTest.gridLayout->itemAtPosition(3,3);
    QVERIFY(button!=0);
    QCOMPARE(button->widget()->objectName(),QString("pushButton_15"));
//4)
    QPushButton butRestart;
    QObject::connect(&butRestart,SIGNAL(clicked()),&puzManTest,SLOT(onRestart()));
    butRestart.click();
//5)
    int gridRows=someUiPuzFormTest.gridLayout->rowCount();
    int gridColumns=someUiPuzFormTest.gridLayout->columnCount();

    for (int row=0;row<gridRows;row++)
    {
        for (int column=0;column<gridColumns;column++)
        {
            int listIndex=row*gridColumns+column;
            QLayoutItem* button = someUiPuzFormTest.gridLayout->itemAtPosition(row,column);
            if(button)
            {
                QCOMPARE(initialButtonsOrder.at(listIndex),button->widget()->objectName());
            }
            else
            {
                QCOMPARE(initialButtonsOrder.at(listIndex),QString(" "));
            }
        }
    }
}

QStringList PuzzleManagerTest::initialButtons()
{
    QStringList wO;
    for (int i=1;i<=15;i++)
    {
        wO<<QString("pushButton_%1").arg(i);
    }
    wO<<QString(" ");

    return wO;

}




QTEST_MAIN(PuzzleManagerTest)
#include "puzzlemanagertest.moc"
