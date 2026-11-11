# The online version of Reversi, built using Qt for WebAssembly.
#
# Unlike the desktop and console versions,
# this does not need RibiClasses nor DotMatrix:
# it only needs the Boost headers, set BOOST_INCLUDE_DIR to their folder, e.g.:
#
#   qmake ReversiWebAssembly.pro BOOST_INCLUDE_DIR=/path/to/boost_headers
#
# The folder must contain the 'boost' folder.

TARGET = reversi

include(Reversi.pri)
include(QtReversi.pri)

SOURCES += \
    qtreversiwebdialog.cpp \
    qtmain_webassembly.cpp

HEADERS += \
    qtreversiwebdialog.h

!isEmpty(BOOST_INCLUDE_DIR) {
  INCLUDEPATH += $$BOOST_INCLUDE_DIR
}

DEFINES += REVERSI_NO_TEXTCANVAS NDEBUG

CONFIG += c++17
QT += core gui widgets
