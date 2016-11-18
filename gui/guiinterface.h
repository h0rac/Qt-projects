#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <QObject>


class GuiInterface : public QObject
{
    Q_OBJECT
public:
    explicit GuiInterface(QObject *parent = 0);


signals:

public slots:
};

#endif // GUIINTERFACE_H
