#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <memory>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Board.h"
#include "ConsoleDisplay.h"

static const char screenPanels[] = {30, 30, 60};
static const char screenHeight = 40;

class BattleShip : public Game
{
  public:
    BattleShip(std::istream&, std::ostream&);

    void gameUpdate();

  private:
    std::istream& in_;
    std::ostream& out_;
    ConsoleDisplay display_;
    Board p1Board_, p2Board_;

    HumanPlayer p1_;
    ComputerPlayer p2_;

    uint8_t p1_step_;
    uint8_t p2_step_;

    bool p1_success_;
    bool p2_success_;
};

#endif // BATTLESHIP_H
