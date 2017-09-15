#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>

static int const boardSize = 10;

const size_t maxNameLength = 20;

static const char screenHeight = 60;

const int leftPanelWidth = 30;
const int rightPanelWidth = 30;

const char firstColChar = 'A';
const char lastColChar = 'J';

std::string const shipGridTop =     "        Ship Grid      ";
std::string const attackGridTop = "       Attack Grid     ";
std::string const boardTop =     "  |A|B|C|D|E|F|G|H|I|J|";
std::string const rowStart[boardSize] = {
                                " 1|",
                                " 2|",
                                " 3|",
                                " 4|",
                                " 5|",
                                " 6|",
                                " 7|",
                                " 8|",
                                " 9|",
                                "10|" };

std::string const shipNoHit = "O";
std::string const shipHit = "@";
std::string const boardNoHit = " ";
std::string const boardHit = "X";

std::string const legend =	"---Legend---   \nO Ship         \n@ Ship with hit\nX Missed Attack\n";




#endif // HELPER_HPP
