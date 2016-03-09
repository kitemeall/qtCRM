#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "groupform.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUrl url = QUrl("https://oauth.vk.com/authorize?client_id=5311096&display=mobile&scope=262144&response_type=token&v=5.45");
    ui->webView->load(url);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_webView_urlChanged(const QUrl &url)
{
    QString urlString = url.toString();
    //Checking if authentication done and we have token
    if(urlString.contains("access_token")){
        //Magic with getting token and id
        QStringList list = urlString.split("=");
        QString token = list.value(1).split("&").value(0);
        QString userId = list.value(3);

        qDebug() << "Token = " << token;
        qDebug() << "Id = " << userId;

        emit gotUser(userId, token);
        this->hide();

    }
}
