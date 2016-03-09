#ifndef GROUPFORM_H
#define GROUPFORM_H

#include <QWidget>
#include<QUrlQuery>

namespace Ui {
class GroupForm;
}

class GroupForm : public QWidget
{
    Q_OBJECT

public:
    explicit GroupForm(QWidget *parent = 0);
    ~GroupForm();

public slots:
    void getGroups(QString userId, QString token);

private:
    Ui::GroupForm *ui;
    QByteArray GET(QUrl query);
};

#endif // GROUPFORM_H
