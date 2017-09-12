#include "HumanPlayer.h"
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

HumanPlayer::HumanPlayer(istream& in, ostream& out) :
  in_(in),
  out_(out)
{
  string str;
  do {
    out_ << "Welcome To Battle Ship!!! What is your name (Max 20 chars)?: ";
    in_ >> str;
  } while (str.length() > 20);

  setName(str);
}

bool HumanPlayer::readUserShotInput_(char* col, char* row)
{
  char tempChar;
  string str;

  while(in_.get(tempChar) && isdigit(tempChar)) {
    str.push_back(tempChar);
  }

  *row = atoi(str.c_str());

  if (*row > Board::boardSize || *row < 1) {
    return false;
  }

  if (isalpha(tempChar)) {
    *col = toupper(tempChar);
  }
  else {
    return false;
  }

  if (*col < 'A' || *col > 'J') {
    return false;
  }

  return true;
}

void HumanPlayer::move(char* col, char* row, Board& board)
{
  bool success = false;
  do {
    out_ << "Enter your shot (ex. 1A):";

  while(in_.get() != '\n');

  if (!readUserShotInput_(col, row)) {
    continue;
  }

  success = board.makeAttempt(*col, *row);

  } while (!success);
}
