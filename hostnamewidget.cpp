#include "hostnamewidget.h"
#include "ui_hostnamewidget.h"

HostnameWidget::HostnameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HostnameWidget)
{
    ui->setupUi(this);
    QRegExp regExp("[A-Za-z0-9]{1,20}");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(ui->cancelButton,&QPushButton::clicked,this,&HostnameWidget::close);
    //connect(ui->lineEdit,&QLineEdit::textChanged,this,&HostnameWidget::setHostname);
    connect(ui->okBtn,&QPushButton::clicked,this,&HostnameWidget::okSelected);
}

QString HostnameWidget::getTextData()
{
    qDebug()<<"before return"<<data;
    return ui->lineEdit->text();
}

void HostnameWidget::setGNetDevPtr(GNetDevice *ptr)
{
    dev = ptr;
    this->show();

}

HostnameWidget::~HostnameWidget()
{
    delete ui;
}
void HostnameWidget::setHostname()
{
    data = ui->lineEdit->text();

}
void HostnameWidget::okSelected()
{
    data = ui->lineEdit->text();
    if (!data.isEmpty())
    {
        dev->setHostname(data);
    }
    else
    {
        qDebug()<<"Error,empty lineEdit";
    }

    this->close();
}



