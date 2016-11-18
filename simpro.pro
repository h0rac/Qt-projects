#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T14:27:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpro
TEMPLATE = app


SOURCES += main.cpp\
    gscene.cpp \
    windows/stpwindow.cpp \
    windows/mainwindow.cpp \
    gui/gnetdevice.cpp \
    gui/gdevwidget.cpp \
    gui/gdevconnector.cpp \
    EntitySystem/EntityManager/entity.cpp \
    EntitySystem/EntityManager/entitymanager.cpp \
    EntitySystem/Systems/system.cpp \
    EntitySystem/EntityManager/entityfactory.cpp \
    EntitySystem/Systems/connectionsystem.cpp \
    core/coreinterface.cpp \
    gui/guiinterface.cpp \
    EntitySystem/Systems/hostnamesystem.cpp \
    gui/mapper.cpp \
    gui/gpacket.cpp \
    hostnamewidget.cpp \
    core/sysmanager.cpp \
    EntitySystem/Systems/stpsystem.cpp

HEADERS  += \
    windows/mainwindow.h \
    gui/gnetdevice.h \
    windows/stpwindow.h \
    gscene.h \
    actdevmodel.h \
    gui/gdevwidget.h \
    gui/gdevconnector.h \
    EntitySystem/Components/component.h \
    EntitySystem/Components/netinterfacecomponent.h \
    EntitySystem/Components/stpcomponent.h \
    EntitySystem/EntityManager/entity.h \
    EntitySystem/EntityManager/entitymanager.h \
    EntitySystem/Systems/system.h \
    EntitySystem/EntityManager/entityfactory.h \
    EntitySystem/Systems/connectionsystem.h \
    core/coreinterface.h \
    EntitySystem/Components/hostnamecomponent.h \
    gui/guiinterface.h \
    EntitySystem/Systems/hostnamesystem.h \
    gui/mapper.h \
    EntitySystem/Components/hwaddrcomponent.h \
    gui/gpacket.h \
    hostnamewidget.h \
    core/sysmanager.h \
    EntitySystem/Systems/stpsystem.h \
    EntitySystem/Components/portcomponent.h \
    EntitySystem/Components/connectioncomponent.h


FORMS    += mainwindow.ui \
    stpwindow.ui \
    hostnamewidget.ui

DISTFILES += \
    UMLsim.qmodel \
    enity-design.qmodel \
    entity2.qmodel

RESOURCES = icons/res.qrc

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
