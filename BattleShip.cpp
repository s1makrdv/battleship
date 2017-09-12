#include <string>
#include "BattleShip.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

BattleShip::BattleShip(istream& input, ostream& output) :
                in_(input),
                out_(output),
                display_(screenPanels, sizeof(screenPanels), screenHeight),
                firstPlayerBoard_(in_, out_),
                secondPlayerBoard_(in_, out_),
                firstPlayer_(in_, out_),
                secondPlayer_(),
                firstPlayerStep_(0),
                secondPlayerStep_(0),
                isFirstPlayerSuccess_(true),
                isSecondPlayerSuccess_(false)
{
  firstPlayerBoard_.placeShips();
  secondPlayerBoard_.placeShips();
  display_.clear();
}

void BattleShip::gameUpdate()
{
  firstPlayerBoard_.writeShipGrid(display_);
  firstPlayerBoard_.writeAttackGrid(display_);
  display_.refresh();

  display_.clear();

  if(isFirstPlayerSuccess_ && !isSecondPlayerSuccess_){
    firstPlayer_.move(&column_, &row_, firstPlayerBoard_);
    firstPlayerStep_++;
    if (secondPlayerBoard_.checkShot(column_, row_, shipName_)) {
      display_.write(2, firstPlayer_.name() + " hit " + secondPlayer_.name() + "'s" + " " + shipName_);
      firstPlayerBoard_.markHit(column_, row_);
    }
    else{
      display_.write(2, firstPlayer_.name() + " missed!!!");
      isFirstPlayerSuccess_ = false;
      isSecondPlayerSuccess_ = true;
    }
  }

  if(!isFirstPlayerSuccess_ && isSecondPlayerSuccess_){
    secondPlayer_.move(&column_, &row_, secondPlayerBoard_);
    secondPlayerStep_++;
    if (firstPlayerBoard_.checkShot(column_, row_, shipName_)) {
      display_.write(2, secondPlayer_.name() + " hit " + firstPlayer_.name() + "'s" + " " + shipName_);
      secondPlayerBoard_.markHit(column_, row_);
      secondPlayer_.update(column_, row_);
    }
    else{
      display_.write(2, "Computer missed!!!");
      isFirstPlayerSuccess_ = true;
      isSecondPlayerSuccess_ = false;
    }
  }

  display_.write(firstPlayer_.name() + " make: " + to_string(firstPlayerStep_) + " shoot's");
  display_.write(secondPlayer_.name() + " make: " + to_string(secondPlayerStep_) + " shoot's\n ");

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


