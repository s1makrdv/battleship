#include "ConsoleDisplay.h"
#include "Helper.hpp"

using namespace std;

ConsoleDisplay::ConsoleDisplay(const char widths[],
                               const char panels,
                               const char height) :
                                 widths_(widths, widths + panels),
                                 height_(height),
                                 panels_(panels),
                                 lastRow_(0)
{
  for (int i = 0; i < panels_; ++i)
    screen_.push_back(vector<string>());

  for (ScreenIt screenIt = screen_.begin(); screenIt != screen_.end(); ++screenIt)
    for (int i = 0; i < height_; ++i)
      (*screenIt).push_back(string());
}

void ConsoleDisplay::clear()
{
  for (ScreenIt screenIt = screen_.begin(); screenIt != screen_.end(); ++screenIt)
    for (PanelIt panelIt = (*screenIt).begin(); panelIt != (*screenIt).end(); ++panelIt)
      (*panelIt).clear(); // Clear string

  lastRow_ = 0;
  stream_.clear();
}

void ConsoleDisplay::refresh()
{
  system("cls"); // FOR WINDOWS
  //system("clear"); // FOR LINUX
  vector<string> screenOut(lastRow_ + 1);

  char panel = 0;

  for (ScreenIt screenIt = screen_.begin(); screenIt != screen_.end(); ++screenIt) {
    PanelIt panelIt = (*screenIt).begin();
    for (PanelIt screenOutIt = screenOut.begin(); screenOutIt != screenOut.end(); ++screenOutIt) {
      try {
        // Append panel string plus padding
        (*screenOutIt) += ((*panelIt) + string(widths_[panel] - (*panelIt).length(), ' ') + "  ");
      }
      catch (const length_error& le) {
        (*screenOutIt) += ((*panelIt) + "  ");
      }
      ++panelIt;
    }
    ++panel;
  }

  // Output each row of the screen
  for (PanelIt panelIt = screenOut.begin(); panelIt != screenOut.end(); ++panelIt)
    cout << *panelIt << endl;

  // Output stream after panels
  for (PanelIt panelIt = stream_.begin(); panelIt != stream_.end(); ++panelIt)
    cout << *panelIt << endl;
}

void ConsoleDisplay::write(const unsigned char panel,
                           const unsigned char row,
                           const string& str)
{
  if (panel >= panels_)
    return;
  else if (row >= height_)
    return;
  else if (widths_[panel] < (screen_[panel][row].length() + str.length()))
    return;
  else
    screen_[panel][row] += str;

  if (lastRow_ < row)
    lastRow_ = row;
}

void ConsoleDisplay::write(const unsigned char panel, const string& str)
{
  if (panels_ <= panel)
    return;
  else if (str.length() > widths_[panel])
    return;

  char row = 0;
  PanelIt panelIt = screen_[panel].begin();
  while ((panelIt != screen_[panel].end()) && (!(*panelIt).empty())) {
    ++panelIt;
    ++row;
  }

  if (height_ <= row)
    return;

  (*panelIt) += str;

  if (lastRow_ < row)
    lastRow_ = row;
}

void ConsoleDisplay::write(const string& str)
{
  stream_.push_back(str);
}
