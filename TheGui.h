#ifndef THEGUI_H
#define THEGUI_H
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QObject>
#include <QTableWidget>
#include "GetCG.h"
class TheGui:public QObject
{
    Q_OBJECT
    QProgressBar *pBar;
    GetCG *cg;
    QWidget *widget;
    QGridLayout *layout;
    QPushButton *getGpaButton;
    QTableWidget *attendanceTable;
    QLabel *regnoLabel;
    QLabel *bdayLabel;
    //QLabel *gpaLabel;

    QLineEdit *regno;
    QLineEdit *bday;
public:
    TheGui();
    void makeGui();
   // void makeRequest(QString,QString);
public slots:
    //QString getReply();
    void buttonClicked();

};

#endif // THEGUI_H
