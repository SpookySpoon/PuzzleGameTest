#include <QApplication>
#include <QtTest/QtTest>
#include "puzzleform.h"
#include "puzbutton.h"


class PuzButtonTest : public QObject
{
    Q_OBJECT
    private slots:
    void testPuzzleButtons();

//В закомменченных ниже тестах я пытался сделать тоже самое, что и в предыдущем, но там почему-то выледает программа
//со словами The program has unexpectedly finished.


//    void testPuzzleButtonsDataDriven();
//    void testPuzzleButtonsDataDriven_data();
};

//Цель теста - убедиться, что не упали настройки QGridLayout в котором существуют кнопки пазла
//Прокликивая поочередно все 15 кнопок мы убеждаемся, что границы QGridLayout не нарушаются
//При заданном порядке кнопки должны переместиться всего два раза (нижняя правая кнопка сначала делает шаг вправо, а потом шаг влево)
void PuzButtonTest::testPuzzleButtons()
{
    PuzzleForm w;
    w.show();
    int moves=0;
    for (int x=0; x<4; x++)
    {
        for (int y=0; y<4; y++)
        {
            PuzButton* pB=qobject_cast<PuzButton*>(w.childAt(w.width()/5*x+50,w.height()*y/4+50));
            if(pB)
            {
                QSignalSpy jB(pB, SIGNAL(moved()));
                QTest::mouseClick(pB,Qt::LeftButton,Qt::NoModifier,QPoint(5,5),1);
                moves+=jB.count();
            }
        }
    }
    QCOMPARE(moves,2);
}


//void PuzButtonTest::testPuzzleButtonsDataDriven()
//{
//    PuzzleForm w;
//    w.show();
//    QFETCH(bool,buttonMoved);
//    QFETCH(QPoint,Coordinates);
//    PuzButton* pB=qobject_cast<PuzButton*>(w.childAt(Coordinates));
//    QSignalSpy jB(pB, SIGNAL(moved()));
//    QTest::mouseClick(pB,Qt::LeftButton,Qt::NoModifier,QPoint(5,5),100);
//    if(buttonMoved)
//    {
//        QCOMPARE(jB.count(),1);
//    }
//    else
//    {
//        QCOMPARE(jB.count(),0);
//    }

//}
//void PuzButtonTest::testPuzzleButtonsDataDriven_data()
//{
//    QTest::addColumn<QPoint>("Coordinates");
//    QTest::addColumn<bool>("buttonMoved");
//    for (int x=0; x<4; x++)
//    {
//        for (int y=0; y<4; y++)
//        {
//            QString title = QString("Column: %1, Row: %2").arg(x).arg(y);
//            if(y!=3||(y=3&&x<2))
//            {
//                QTest::newRow(title.toLatin1().data()) << QPoint(581/5*x+50, 512/4*y+50) << false;
//            }
//            else
//            {
//                QTest::newRow(title.toLatin1().data()) << QPoint(581/5*x+50, 512/4*y+50) << true;
//            }
//        }
//    }
//}




QTEST_MAIN(PuzButtonTest)
#include "puzbuttontest.moc"
