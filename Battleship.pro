QT += core
QT -= gui

CONFIG += c++11

TARGET = battleship
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += BattleShip.h \
    BS_Board.h\
    BS_BoardTile.h\
    BS_ComputerPlayer.h\
    BS_HumanPlayer.h\
    BS_Player.h\
    BS_ShipTile.h\
    BS_Strategy.h\
    BS_Tile.h\
    ConsoleDisplay.h\
    Coord.h\
    Game.h\
    Ship.h

SOURCES += main.cpp \
    Ship.cpp\
    BattleShip.cpp\
    BS_Board.cpp\
    BS_ComputerPlayer.cpp\
    BS_HumanPlayer.cpp\
    BS_Strategy.cpp\
    ConsoleDisplay.cpp


DEFINES += QT_DEPRECATED_WARNINGS


