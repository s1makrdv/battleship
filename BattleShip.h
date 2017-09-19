#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <memory>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Board.h"
#include "ConsoleDisplay.h"

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

    HumanPlayer    firstPlayer_;
    ComputerPlayer secondPlayer_;

    char col_, row_;

    std::string shipName_;
    void checkFleetSunk_(Board& firstBoard,
                         Board& secondBoard,
                         Player& player);
    void playerStep_(Board& firstBoard,
                     Board& secondBoard,
                     Player& firstPlayer,
                     Player& secondPlayer);
};

#endif // BATTLESHIP_H
