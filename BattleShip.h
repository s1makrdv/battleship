#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <memory>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Board.h"
#include "ConsoleDisplay.h"

static const char screenHeight = 60;

const int leftPanelWidth = 30;
const int rightPanelWidth = 30;

static const char screenPanels[] = { leftPanelWidth,
                                     rightPanelWidth,
                                     screenHeight };


class BattleShip : public Game
{
  public:
    BattleShip(std::istream&, std::ostream&);

    void gameUpdate();

  private:
    std::istream& in_;
    std::ostream& out_;
    ConsoleDisplay display_;
    Board firstPlayerBoard_, secondPlayerBoard_;

    HumanPlayer firstPlayer_;
    ComputerPlayer secondPlayer_;

    uint8_t firstPlayerStep_;
    uint8_t secondPlayerStep_;

    bool isFirstPlayerSuccess_;
    bool isSecondPlayerSuccess_;

    char column_, row_;
    std::string shipName_;
};

#endif // BATTLESHIP_H
