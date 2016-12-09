#include <QApplication>
#include <QDebug>
#include "puzzleform.h"
#include "puzbutton.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleForm w;
    w.show();
    w.ubMoves(100);
    qDebug()<<w.getMoves();
    return a.exec();
}
