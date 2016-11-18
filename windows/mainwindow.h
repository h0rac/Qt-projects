#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QIcon>
#include <gscene.h>
#include <QListWidget>
#include <QStandardItemModel>
#include <QSplitter>
#include <core/sysmanager.h>

class GScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QListView *getActDevListView();

    ~MainWindow();

private slots:
    void getToolList();
    void getItemList();
    void setProtoWindow();

    void startClicked();
    void stopClicked();
    void stepForwardClicked();
    void stepBackwardClicked();
    void pauseClicked();

private:
    QList<QString>protocols;
    GScene *pscene;
    bool status;
    Ui::MainWindow *ui;

    void setToolList();
    void setItemList();
    void setProtoList();




};

#endif // MAINWINDOW_H
