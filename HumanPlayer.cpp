#include "HumanPlayer.h"
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

const size_t maxNameLength = 20;

HumanPlayer::HumanPlayer(istream& in, ostream& out) :
  in_(in),
  out_(out)
{
  string str;
  do {
    out_ << "Welcome To Battle Ship!!! What is your name (Max 20 chars)?: ";
    in_ >> str;
  } while (str.length() > maxNameLength);

  setName(str);
}

bool HumanPlayer::readUserShotInput_(char* col, char* row)
{
  char c;
  string str;

  while(in_.get(c) && isdigit(c)) {
    str.push_back(c);
  }

  *row = atoi(str.c_str());

  if (*row > boardSize || *row < 1) {
    return false;
  }

  if (isalpha(c)) {
    *col = toupper(c);
  }
  else {
    return false;
  }

  if (*col < firstColChar || *col > lastColChar) {
    return false;
  }

  return true;
}

void HumanPlayer::move(char* col, char* row, Board& board)
{
  bool isSuccess = false;
  do {
    out_ << "Enter your shot (ex. 1A):";

  while(in_.get() != '\n');

  if (!readUserShotInput_(col, row)) {
    continue;
  }

  isSuccess = board.makeAttempt(*col, *row);

  } while (!isSuccess);
}
