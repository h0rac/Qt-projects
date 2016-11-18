#ifndef STPWINDOW_H
#define STPWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QStandardItemModel>

namespace Ui {
class StpWindow;
}

class StpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StpWindow(QWidget *parent = 0);
    QListView *setSTPactDevView();
    void setStpModel(QStandardItemModel *model);


    ~StpWindow();

private:
    Ui::StpWindow *ui;
    QStandardItemModel *stpmodel;

private slots:
    void getSTPViewItem();

};

#endif // STPWINDOW_H
