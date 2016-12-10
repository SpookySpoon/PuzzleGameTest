#include <QApplication>
#include <QDebug>
#include "puzzleform.h"
#include "puzbutton.h"
#include "ui_puzzleform.h"
#include <QtTest/QtTest>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleForm w;
    QPushButton* opaButton =w.ui->buttonShuffle;
    w.show();
    QPoint opa(w.width()/2,w.height()*7/8);
    QWidget* obanaWid = w.childAt(opa);
    if(obanaWid)
    {
        qDebug()<<obanaWid->objectName();
    }
    QSignalSpy opaSpy(&w,SIGNAL(moveTrySpy()));
    QTest::mouseClick(obanaWid,Qt::LeftButton,Qt::NoModifier,QPoint(5,5),100);

//    w.ubMoves(100);
    qDebug()<<opaSpy.count();
    return a.exec();
}
