QT -= core
QT -= gui

CONFIG += c++11

TARGET = battleship
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += BattleShip.h \
    ConsoleDisplay.h \
    Coord.h \
    Game.h \
    Ship.h \
    Board.h \
    BoardTile.h \
    ComputerPlayer.h \
    HumanPlayer.h \
    Player.h \
    ShipTile.h \
    Strategy.h \
    Tile.h

SOURCES += main.cpp \
    Ship.cpp \
    BattleShip.cpp \
    ConsoleDisplay.cpp \
    Board.cpp \
    ComputerPlayer.cpp \
    HumanPlayer.cpp \
    Strategy.cpp \
    Tile.cpp


DEFINES += QT_DEPRECATED_WARNINGS


