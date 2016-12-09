#include <QApplication>
#include <QDebug>
#include "puzzleform.h"
#include "puzbutton.h"
#include <QtTest/QtTest>




class DateTest : public QObject
{
    Q_OBJECT
    private slots:

    void testSignals();
};

void DateTest::testSignals()
{
    PuzzleForm w;
    PuzButton pB;
    int moves=0;
    for (int i=1; i<=4; i++)
    {
        for (int i1=1; i1<=4; i1++)
        {
            QSignalSpy jB(&w, SIGNAL());
            QPoint upButton = QPoint(114*i, 120*i1 );
            QTest::mouseClick(&w,Qt::LeftButton,0,upButton);
            moves=w.getMoves();
        }
    }

    QCOMPARE(moves,2);
    qDebug()<<moves;
}

QTEST_MAIN(DateTest)
#include "main.moc"



//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    PuzzleForm w;
//    PuzButton pB;
//    int moves=0;
//    for (int i=1; i<=4; i++)
//    {
//        for (int i1=1; i1<=4; i1++)
//        {
//            QSignalSpy jB( &pB, SIGNAL(moved()));
//            QPoint upButton = QPoint(114*i, 120*i1 );
//            QTest::mouseClick(&w,Qt::LeftButton,0,upButton);
//            moves+=jB.count();
//        }
//    }
//    qDebug()<<moves;



//    w.show();
//    return a.exec();
//}
