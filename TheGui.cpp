#include "TheGui.h"

TheGui::TheGui()
{

}
void TheGui::makeGui()
{
    getGpaButton = new QPushButton("Get Bunks");
    regnoLabel = new QLabel("Reg no:");
    bdayLabel = new QLabel("Bday(yyyy-mm-dd):");
    //gpaLabel = new QLabel("Gpa");
    regno = new QLineEdit("110905424");
    bday = new QLineEdit("1993-06-26");
    pBar = new QProgressBar();
    attendanceTable = new QTableWidget(6,2);


    attendanceTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Subject"));
    attendanceTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Bunks"));


    pBar->setOrientation(Qt::Horizontal);

    QGridLayout *layout = new QGridLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();
    layout->addWidget(regnoLabel,0,0);
    layout->addWidget(regno,0,1);
    layout->addWidget(bdayLabel,1,0);
    layout->addWidget(bday,1,1);
    layout->addWidget(pBar,2,0);
    layout->addWidget(getGpaButton,2,1);
    vlayout->addLayout(layout);
    vlayout->addWidget(attendanceTable);
    widget = new QWidget();
    widget->setLayout(vlayout);
    widget->setWindowTitle("MIT Bunks Getter");
    widget->show();

    connect(getGpaButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));

}
void TheGui::buttonClicked()
{
    int count = 0;
    pBar->setMaximum(0);
    pBar->setMinimum(0);
    pBar->setValue(count++);
    cg = new GetCG();
    cg->makeRequest(regno->text(),bday->text(),pBar);
    QString *subjects;
    QString *c;

    subjects = cg->getAttendance();
    c= cg->getCourses();

    attendanceTable->setItem(0,0,new QTableWidgetItem(c[0]));
    attendanceTable->setItem(1,0,new QTableWidgetItem(c[1]));
    attendanceTable->setItem(2,0,new QTableWidgetItem(c[2]));
    attendanceTable->setItem(3,0,new QTableWidgetItem(c[3]));
    attendanceTable->setItem(4,0,new QTableWidgetItem(c[4]));
    attendanceTable->setItem(5,0,new QTableWidgetItem(c[5]));

    attendanceTable->setItem(0,1,new QTableWidgetItem(subjects[0]));
    attendanceTable->setItem(1,1,new QTableWidgetItem(subjects[1]));
    attendanceTable->setItem(2,1,new QTableWidgetItem(subjects[2]));
    attendanceTable->setItem(3,1,new QTableWidgetItem(subjects[3]));
    attendanceTable->setItem(4,1,new QTableWidgetItem(subjects[4]));
    attendanceTable->setItem(5,1,new QTableWidgetItem(subjects[5]));

    attendanceTable->resizeColumnsToContents();

}
