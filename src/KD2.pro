#-------------------------------------------------
#
# Knowledge Discovery (KD-LADS) project, Version 2
#
#
# Author: Morteza Ansarinia <morteza.ansari@gmail.com>
#
#-------------------------------------------------

QT       += core gui

TARGET = KD2

TEMPLATE  = app
CONFIG   += console
CONFIG   += qtestlib
CONFIG   -= app_bundle

# use mpi compilers instead of default c++ compilers
QMAKE_CC     = mpicc
QMAKE_CXX    = mpic++
QMAKE_CFLAGS = $$system(mpicc --showme:compile)
QMAKE_CXXFLAGS = $$system(mpic++ --showme:compile)
QMAKE_LFLAGS = $$system(mpic++ --showme:link)
QMAKE_LINK = mpic++

SOURCES += \
    main.cpp \
    ui/SideBar.cpp \
    ui/MainWindow.cpp \
    ui/SideBarLabel.cpp \
    ui/ActivitiesPage.cpp \
	ui/StartPage.cpp \
	ui/KMeansPage.cpp \
	ui/SOMPage.cpp \
	ui/PCAPage.cpp \
	parallel/Communicator.cpp \
    math/EigenValueDecomposition.cpp \
    math/Matrix.cpp \
    math/Vector.cpp \
    test/TestEVD.cpp

RESOURCES += \
    KD2.qrc

HEADERS += \
    ui/SideBar.h \
    ui/MainWindow.h \
    ui/SideBarLabel.h \
    ui/ActivitiesPage.h \
    ui/StartPage.h \
	ui/KMeansPage.h \
	ui/SOMPage.h \
	ui/PCAPage.h \
	core/KD2Constants.h \
	parallel/Communicator.h \
    math/EigenValueDecomposition.h \
    math/Matrix.h \
    math/Vector.h \
    core/AlgorithmInterface.h \
    core/DatasetInterface.h \
    ui/PageInterface.h

FORMS += \
    ui/MainWindow.ui \
    ui/SideBarLabel.ui \
    ui/ActivitiesPage.ui \
	ui/StartPage.ui \
	ui/KMeansPage.ui \
	ui/SOMPage.ui \
	ui/PCAPage.ui
