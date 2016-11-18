#ifndef HOSTNAMEWIDGET_H
#define HOSTNAMEWIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include <QDebug>
#include <gui/mapper.h>

class GNetDevice;

namespace Ui {
class HostnameWidget;
}

class HostnameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HostnameWidget(QWidget *parent = 0);
    QString getTextData();
    void setGNetDevPtr(GNetDevice * ptr);
    ~HostnameWidget();


private:
    Ui::HostnameWidget *ui;
    QString data;
    GNetDevice * dev;

private slots:
    void okSelected();
    void setHostname();
};

#endif // HOSTNAMEWIDGET_H
