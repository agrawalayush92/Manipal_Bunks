#include "GetCG.h"
#include <QDebug>
#include <QMessageBox>

GetCG::GetCG()
{
}
void GetCG::makeRequest(QString regNo,QString bday,QProgressBar *pBar)
{

    QUrl serviceUrl = QUrl("http://218.248.47.9/websis/control/createAnonSession");
    QByteArray postData;

    QUrl params; // Add the query element to the url
    params.addQueryItem("idValue",regNo);
    params.addQueryItem("birthDate_i18n",bday);
    params.addQueryItem("birthDate",bday);

    postData = params.encodedQuery(); //Encode the URL in the % form,

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    networkManager->setCookieJar(new QNetworkCookieJar(this));//To save the cookies

    QNetworkRequest req; // = new QNetworkRequest();
    req.setUrl(serviceUrl);
    reply= networkManager->post(req, postData); // Request the data from the form

    QEventLoop loop; //Wait until data has been fetched
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();

    QString replyText = reply->readAll(); //Get the entire page
    if(!replyText.contains("EXIT"))
    {
        gpa = "Invalid Logins";
        pBar->setMinimum(0);
        pBar->setMaximum(1);
        return;
    }
    QList<QNetworkCookie>  cookies = networkManager->cookieJar()->cookiesForUrl(serviceUrl);//Fetch the cookies of the current URL
    QVariant var;
    var.setValue(cookies);

    req.setUrl(QUrl("http://websismit.manipal.edu/websis/control/StudentAcademicProfile"));
    req.setHeader(QNetworkRequest::CookieHeader, var); //Add the cookies to current URL,so you can continue

    reply= networkManager->get(req);

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));//Wait until loop ends

   loop.exec();
   pBar->setMinimum(0);
   pBar->setMaximum(1);//Set Progress Bar

   replyText = reply->readAll(); //Get entire source
   QRegExp rx("(.*)CGPA(.*)large-text\">(.*)<\\/span>"); //Regex To get the GPA
   rx.exactMatch(replyText);
   gpa = rx.cap(3); //Cap is the position of the gpa starting from 1
   gpa.resize(4); //Since apparently cap also gets the whole page
    //qDebug( reply->readAll());

   QString pat;
   int j=0;
   attend = new QString[6];
   for(int i=1;i<=6;i++)
   {

       pat = QString("(.*)cc_ListAttendanceSummary_classesAbsent_%1(.*)<\\/span>").arg(i);
       rx.setPattern(pat);
       rx.exactMatch(replyText);

       attend[j]=rx.cap(2);
       attend[j].remove(0,25);
       attend[j].resize(1);
       //qDebug()<<attend[j];

       j++;

    }

   //Get the courses

   courses = new QString[6];
   j=0;
   QRegExp rmvamp("&(.*);");
   QRegExp replaceamp("&amp;");
   for(int i=0;i<6;i++)
   {
       pat = QString("(.*)cc_ListAttendanceSummary_productName_%1(.*)<\\/span>").arg(i+1);
       rx.setPattern(pat);
       rx.exactMatch(replyText);

       courses[i]=rx.cap(2);
       courses[i].remove(0,25);
       courses[i]=courses[i].left(courses[i].indexOf('<',0));

       if(courses[i].contains(rmvamp))
         {
           while(courses[i].contains(rmvamp))
           {
              courses[i].remove(rmvamp);

           }
          }


           if(courses[i].contains(replaceamp))
           {
               while(courses[i].contains(replaceamp))
               {
                   courses[i].replace(replaceamp,"&");
               }
           }



   }


      // courses[j]=temp;
       //qDebug()<<courses[j];

}



QString GetCG::getReply()
{

    return gpa; //Return the GPA
}

QString* GetCG::getAttendance()
{
    return attend;
}

QString* GetCG::getCourses()
{
    return courses;
}
