#include <string>
#include "BattleShip.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

BattleShip::BattleShip(istream& input, ostream& output) :
                in_(input),
                out_(output),
                col_(0),
                row_(0),
                display_(screenPanels, sizeof(screenPanels), screenHeight),
                firstPlayerBoard_(in_, out_),
                secondPlayerBoard_(in_, out_),
                firstPlayer_(in_, out_),
                secondPlayer_()
{
  firstPlayerBoard_.placeShips();
  secondPlayerBoard_.placeShips();

  firstPlayer_.setIsSuccess(true);
  secondPlayer_.setIsSuccess(false);

  firstPlayer_.setStepNo(0);
  secondPlayer_.setStepNo(0);

  display_.clear();
}

void BattleShip::gameUpdate()
{
  firstPlayerBoard_.writeShipGrid(display_);
  firstPlayerBoard_.writeAttackGrid(display_);
  display_.refresh();

  display_.clear();

  playerStep_(firstPlayerBoard_,
              secondPlayerBoard_,
              firstPlayer_,
              secondPlayer_);

  playerStep_(secondPlayerBoard_,
              firstPlayerBoard_,
              secondPlayer_,
              firstPlayer_);

  display_.write(firstPlayer_.name() +
                 " make: " +
                 to_string(firstPlayer_.stepNo()) +
                 " shoot's");

  display_.write(secondPlayer_.name() +
                 " make: " +
                 to_string(secondPlayer_.stepNo()) +
                 " shoot's\n ");

  checkFleetSunk_(firstPlayerBoard_, secondPlayerBoard_, firstPlayer_);
  checkFleetSunk_(secondPlayerBoard_, firstPlayerBoard_, secondPlayer_);



}

void BattleShip::checkFleetSunk_(Board& firstBoard, Board& secondBoard, Player& player)
{
  if (firstBoard.isSunkFleet()) {
    secondBoard.writeShipGrid(display_);
    secondBoard.writeAttackGrid(display_);
    display_.write(2, player.name() + " wins!!!");
    display_.refresh();
    gameEnd();
  }
}

void BattleShip::playerStep_(Board& firstBoard,
                             Board& secondBoard,
                             Player& firstPlayer,
                             Player& secondPlayer)
{
  if(firstPlayer.isSuccess() && !secondPlayer.isSuccess() ){
    firstPlayer.move(&col_, &row_, firstBoard);
    firstPlayer.setStepNo();
    if (secondBoard.checkShot(col_, row_, shipName_)) {
      display_.write(2, firstPlayer.name() + " hit " +
                     secondPlayer.name() +
                     "'s" + " " +
                     shipName_);

      firstBoard.markHit(col_, row_);
      secondPlayer.update(col_, row_);
    }
    else{
      display_.write(2, firstPlayer.name() + " missed!!!");
      firstPlayer.setIsSuccess(false);
      secondPlayer.setIsSuccess(true);
    }
  }
}


