#include "groupform.h"
#include "ui_groupform.h"
#include <QDebug>
#include<QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QTimer>
#include<QEventLoop>
#include<QTableView>
#include<QStandardItemModel>
#include "json.h"
using namespace QtJson;
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


    QUrlQuery current("https://api.vk.com/method/groups.get?");
    current.addQueryItem("v", "5.3");
    current.addQueryItem("user_id", userId);
    current.addQueryItem("extended", "1");
    current.addQueryItem("filter", "admin");
    current.addQueryItem("access_token", token);
    QUrl url(current.toString());
    QByteArray answer = GET(url);
    if(answer.isEmpty()){
        qDebug()<<"Empty answer from server";
        exit(-1);
    }
    QVariantList list = parse(answer)
            .toMap()
            .value("response")
            .toMap()
            .value("items")
            .toList();
    setGroupsView(list);

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
void GroupForm::setGroupsView(QVariantList list){
    QStandardItemModel * model = new QStandardItemModel(list.size(), 2, this);
    QStringList headerLabels;
    headerLabels.append("id");
    headerLabels.append("Group name");
    model->setHorizontalHeaderLabels(headerLabels);
    for(int row = 0; row < list.size(); row++){
        QVariantMap map = list.value(row).toMap();

        QVariant id = map.find("id").value();
        QModelIndex index = model->index(row, 0);
        model->setData(index,id);

        QVariant groupName = map.find("name").value();
        index = model->index(row, 1);
        model->setData(index,groupName);


    }
    ui->tableView->setModel(model);

}
