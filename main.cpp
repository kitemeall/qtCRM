#include "mainwindow.h"
#include "groupform.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *utfCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfCodec);
    MainWindow w;
    w.show();
    GroupForm groupForm;
    QObject::connect(&w,SIGNAL(gotUser(QString,QString)), &groupForm, SLOT(getGroups(QString,QString)));


    return a.exec();
}
