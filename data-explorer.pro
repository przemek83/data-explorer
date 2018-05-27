TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Dataset.cpp \
    FileDataLoader.cpp \
    Column.cpp \
    IntegerColumn.cpp \
    StringColumn.cpp \
    UserInterface.cpp \
    Operation.cpp

HEADERS += \
    Dataset.h \
    DataLoader.h \
    FileDataLoader.h \
    Column.h \
    IntegerColumn.h \
    StringColumn.h \
    Operation.h \
    UserInterface.h \
    Query.h
