#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T15:17:56
#
#-------------------------------------------------

QT       += core gui axcontainer widgets
#CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReimbursementDocument
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtexcel.cpp \
    qttools.cpp \
    qtperinfodlg.cpp \
    qtticket.cpp \
    qtlabel.cpp \
    qttextedit.cpp \
    qdatecompute.cpp \
    qtreimdomestic.cpp \
    qdetailform.cpp \
    qdetailformmodel.cpp \
    qtlineedit.cpp \
    qtworkcalender.cpp \
    qteportstring.cpp \
    qtreimdomestic_f.cpp \
    qtexchangerate.cpp \
    qdetailform_f.cpp

HEADERS  += mainwindow.h \
    data.h \
    qtexcel.h \
    qttools.h \
    qtperinfodlg.h \
    qtticket.h \
    qtlabel.h \
    qttextedit.h \
    qdatecompute.h \
    qtreimdomestic.h \
    qdetailform.h \
    qdetailformmodel.h \
    qtlineedit.h \
    qtworkcalender.h \
    qteportstring.h \
    qtreimdomestic_f.h \
    qtexchangerate.h \
    qdetailform_f.h

FORMS    += mainwindow.ui \
    qtperinfodlg.ui \
    qtoffcialticketdlg.ui

DISTFILES +=
