QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++17

TARGET   = DSA_ShoppingSystem
TEMPLATE = app

SOURCES  += main.cpp \
             mainwindow.cpp \
             DSA_Shopping_System.cpp \
             DSA_Ordering_System.cpp \
             DSA_File_Manager.cpp

HEADERS  += mainwindow.h \
             DSA_Storage_System.h \
             DSA_Shopping_System.h \
             DSA_Ordering_System.h \
             DSA_File_Manager.h

DISTFILES += \
    Orders.csv \
    Products.csv \
    Shops.csv \
    Users.csv
