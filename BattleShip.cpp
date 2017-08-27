#include <string>
#include "BattleShip.h"
#include "BS_HumanPlayer.h"
#include "BS_ComputerPlayer.h"

using namespace std;

BattleShip::BattleShip(istream& input, ostream& output) :
				in(input),
				out(output),
				display(screenPanels, sizeof(screenPanels), screenHeight),
				p1Board(in, out),
				p2Board(in, out),
				p1(in, out),
                p2(),
                p1_success(true),
                p2_success(false)
{
    p1Board.placeShips(); // Random human ships placer
    p2Board.placeShips(); // Computer will pick at random
    display.clear();
}

void BattleShip::gameUpdate()
{
	char c, r;
	string str;
    p1Board.writeShipGrid(display);//draw ship grid for Player 1
    p1Board.writeAttackGrid(display);//draw tracking grid for Player 1
	display.refresh();

    display.clear();
    //Player 1 step
    if(p1_success && !p2_success){
        p1.move(&c, &r, p1Board);
        p1_step++;
        if (p2Board.checkShot(c, r, str)) {
            display.write(2, p1.name() + " hit " + p2.name() + "'s" + " " + str);
            p1Board.markHit(c, r);
        }
        else{
            display.write(2, p1.name() + " missed!!!");
            p1_success = false;
            p2_success = true;
        }

    }
    //Player 2(computer) step
    if(!p1_success && p2_success){
        p2.move(&c, &r, p2Board);
        p2_step++;
        if (p1Board.checkShot(c, r, str)) {
            display.write(2, p2.name() + " hit " + p1.name() + "'s" + " " + str);
            p2Board.markHit(c, r);
            p2.update(c, r);
        }
        else{
            display.write(2, "Computer missed!!!");
            p1_success = true;
            p2_success = false;
        }

    }
    //step statistic
    display.write(p1.name() + " make: " + to_string(p1_step) + " shoot's");
    display.write(p2.name() + " make: " + to_string(p2_step) + " shoot's\n ");

    //check game over on board 2
    if (p2Board.fleetSunk()) {
        p2Board.writeShipGrid(display);//draw player 2 board after game over
        p1Board.writeAttackGrid(display);
        display.write(2, p1.name() + " wins!!!");
        display.refresh();
        gameEnd();
        return;
    }
    //check game over on board 1
    if (p1Board.fleetSunk()) {
        p1Board.writeShipGrid(display);
        p1Board.writeAttackGrid(display);
        display.write(2, p2.name() + " wins!!!");
        display.refresh();
        gameEnd();
        return;
    }

}


