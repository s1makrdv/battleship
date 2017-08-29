#include <string>
#include "BattleShip.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

BattleShip::BattleShip(istream& input, ostream& output) :
				in_(input),
				out_(output),
				display_(screenPanels, sizeof(screenPanels), screenHeight),
				p1Board_(in_, out_),
				p2Board_(in_, out_),
				p1_(in_, out_),
                p2_(),
                p1_step_(0),
                p2_step_(0),
                p1_success_(true),
                p2_success_(false)
{
    p1Board_.placeShips(); // Random human ships placer
    p2Board_.placeShips(); // Computer will pick at random
    display_.clear();
}

void BattleShip::gameUpdate()
{
	char c, r;
	string str;
    p1Board_.writeShipGrid(display_);//draw ship grid for Player 1
    p1Board_.writeAttackGrid(display_);//draw tracking grid for Player 1
	display_.refresh();

    display_.clear();
    //Player 1 step
    if(p1_success_ && !p2_success_){
        p1_.move(&c, &r, p1Board_);
        p1_step_++;
        if (p2Board_.checkShot(c, r, str)) {
            display_.write(2, p1_.name() + " hit " + p2_.name() + "'s" + " " + str);
            p1Board_.markHit(c, r);
        }
        else{
            display_.write(2, p1_.name() + " missed!!!");
            p1_success_ = false;
            p2_success_ = true;
        }

    }
    //Player 2(computer) step
    if(!p1_success_ && p2_success_){
        p2_.move(&c, &r, p2Board_);
        p2_step_++;
        if (p1Board_.checkShot(c, r, str)) {
            display_.write(2, p2_.name() + " hit " + p1_.name() + "'s" + " " + str);
            p2Board_.markHit(c, r);
            p2_.update(c, r);
        }
        else{
            display_.write(2, "Computer missed!!!");
            p1_success_ = true;
            p2_success_ = false;
        }

    }
    //step statistic
    display_.write(p1_.name() + " make: " + to_string(p1_step_) + " shoot's");
    display_.write(p2_.name() + " make: " + to_string(p2_step_) + " shoot's\n ");

    //check game over on board 2
    if (p2Board_.fleetSunk()) {
        p2Board_.writeShipGrid(display_);//draw player 2 board after game over
        p1Board_.writeAttackGrid(display_);
        display_.write(2, p1_.name() + " wins!!!");
        display_.refresh();
        gameEnd();
        return;
    }
    //check game over on board 1
    if (p1Board_.fleetSunk()) {
        p1Board_.writeShipGrid(display_);
        p1Board_.writeAttackGrid(display_);
        display_.write(2, p2_.name() + " wins!!!");
        display_.refresh();
        gameEnd();
        return;
    }

}


