#include "groupform.h"
#include "ui_groupform.h"
#include <QDebug>
#include<QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QTimer>
#include<QEventLoop>

GroupForm::GroupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupForm)
{
    ui->setupUi(this);
}

GroupForm::~GroupForm()
{
    delete ui;
}
void GroupForm::getGroups(QString userId, QString token){
    this->show();
    qDebug() << userId << token;

//    "https://api.vk.com/method/groups.get?user_id=23665641&extended=1&filter=admin&"
//    "access_token=38a99ed7514ca68c05b53d5afc9982abae884f6f7b4fcd6c3b5668ce67596d016e2cf8a4d452b39387619"

    QUrlQuery current("https://api.vk.com/method/groups.get?");
    current.addQueryItem("v", "5.3");
    current.addQueryItem("user_id", userId);
    current.addQueryItem("extended", "1");
    current.addQueryItem("filter", "");
    current.addQueryItem("access_token", token);
    QUrl url(current.toString());
    QByteArray answer = GET(url);
    qDebug() << answer;


}
QByteArray GroupForm::GET(QUrl query){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest req(query);
    QNetworkReply * replay = manager->get(req);
    QEventLoop wait;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(10000, &wait, SLOT(quit()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager,SLOT(deleteLater()));
    wait.exec();
    QByteArray ans = replay->readAll();
    replay->deleteLater();
    return ans;

}
