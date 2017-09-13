#include <string>
#include "BattleShip.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

BattleShip::BattleShip(istream& input, ostream& output) :
                in_(input),
                out_(output),
                column_(0),
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

  if(firstPlayer_.isSuccess() && !secondPlayer_.isSuccess() ){
    firstPlayer_.move(&column_, &row_, firstPlayerBoard_);
    firstPlayer_.setStepNo();
    if (secondPlayerBoard_.checkShot(column_, row_, shipName_)) {
      display_.write(2, firstPlayer_.name() + " hit " + secondPlayer_.name() + "'s" + " " + shipName_);
      firstPlayerBoard_.markHit(column_, row_);
    }
    else{
      display_.write(2, firstPlayer_.name() + " missed!!!");
      firstPlayer_.setIsSuccess(false);
      secondPlayer_.setIsSuccess(true);
    }
  }

  if( !firstPlayer_.isSuccess() && secondPlayer_.isSuccess() ){
    secondPlayer_.move(&column_, &row_, secondPlayerBoard_);
    secondPlayer_.setStepNo();
    if (firstPlayerBoard_.checkShot(column_, row_, shipName_)) {
      display_.write(2, secondPlayer_.name() + " hit " + firstPlayer_.name() + "'s" + " " + shipName_);
      secondPlayerBoard_.markHit(column_, row_);
      secondPlayer_.update(column_, row_);
    }
    else{
      display_.write(2, "Computer missed!!!");
      firstPlayer_.setIsSuccess(true);
      secondPlayer_.setIsSuccess(false);
    }
  }

  display_.write(firstPlayer_.name() + " make: " + to_string(firstPlayer_.stepNo()) + " shoot's");
  display_.write(secondPlayer_.name() + " make: " + to_string(secondPlayer_.stepNo()) + " shoot's\n ");

  if (secondPlayerBoard_.isSunkFleet()) {
    secondPlayerBoard_.writeShipGrid(display_);
    firstPlayerBoard_.writeAttackGrid(display_);
    display_.write(2, firstPlayer_.name() + " wins!!!");
    display_.refresh();
    gameEnd();
    return;
  }

  if (firstPlayerBoard_.isSunkFleet()) {
    firstPlayerBoard_.writeShipGrid(display_);
    firstPlayerBoard_.writeAttackGrid(display_);
    display_.write(2, secondPlayer_.name() + " wins!!!");
    display_.refresh();
    gameEnd();
    return;
  }
}


