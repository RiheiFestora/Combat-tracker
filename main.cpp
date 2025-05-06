#include "combat_tracker_main.h"
#include <QtWidgets/QApplication>
/* This program has been made with the use of Qt and is meant for non-commercial use. 
 Its main purpose has been to serve as an educational programming exercise and has been
 done with the help of ChatGPT-4o.*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    combat_tracker_main w;
    w.show();
    return a.exec();
}
