#include "HumanPlayer.h"
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

HumanPlayer::HumanPlayer(istream& i, ostream& o) : in_(i), out_(o)
{
  string str;
  do {
    out_ << "Welcome To Battle Ship!!! What is your name (Max 20 chars)?: ";
    in_ >> str;
  } while (str.length() > 20);

  n_ = str;
}

bool HumanPlayer::readUserShotInput_(char *col, char *row)
{
  char c;
  string str;

  while(in_.get(c) && isdigit(c)) {
    str.push_back(c);
  }

  *row = atoi(str.c_str());

  if (*row > Board::boardSize || *row < 1) {
    return false;
  }

  if (isalpha(c)) {
    *col = toupper(c);
  }
  else {
    return false;
  }

  if (*col < 'A' || *col > 'J') {
    return false;
  }

  return true;
}

void HumanPlayer::move(char* c, char* r, Board& board)
{
  bool success = false;
  do {
    out_ << "Enter your shot (ex. 1A):";

  while(in_.get() != '\n');

  if (!readUserShotInput_(c, r)) {
    continue;
  }

  success = board.makeAttempt(*c, *r);

  } while (!success);
}
