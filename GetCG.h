#ifndef GETCG_H
#define GETCG_H
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QEventLoop>
#include <QRegExp>
#include <QProgressBar>
#include <QtNetwork/QNetworkCookieJar>
//#include <QDebug>
class GetCG:public QObject
{
    Q_OBJECT
public:
    QNetworkReply *reply;
    QString gpa;
    QString *attend;
    QString *courses;
    GetCG();
    void makeRequest(QString,QString,QProgressBar*);
public slots:
    QString getReply();

    QString* getAttendance();
    QString* getCourses();

};

#endif // GETCG_H
