QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/model.cpp \
    QCustomPlot/qcustomplot.cpp \
    View/graph.cpp \
    View/view.cpp \
    main.cpp

HEADERS += \
    View/view.h \
    Model/model.h \
    View/graph.h \
    QCustomPlot/qcustomplot.h \
    Controller/controller.h

FORMS += \
    View/graph.ui \
    View/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
