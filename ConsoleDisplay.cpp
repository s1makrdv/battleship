#include "ConsoleDisplay.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

ConsoleDisplay::ConsoleDisplay(const char widths[],
                               const char panels,
                               const char height) :
                                 w_(widths, widths + panels),
                                 h_(height),
                                 p_(panels),
                                 lastRow_(0)
{
  for (int i = 0; i < p_; ++i)
    screen_.push_back(vector<string>());

  for (screenIt_t s_it = screen_.begin(); s_it != screen_.end(); ++s_it)
    for (int i = 0; i < h_; ++i)
      (*s_it).push_back(string());
}

void ConsoleDisplay::clear()
{
  for (screenIt_t s_it = screen_.begin(); s_it != screen_.end(); ++s_it)
    for (panelIt_t p_it = (*s_it).begin(); p_it != (*s_it).end(); ++p_it)
      (*p_it).clear(); // Clear string

  lastRow_ = 0;
  stream_.clear();
}

void ConsoleDisplay::refresh()
{
  system("cls"); // FOR WINDOWS
  //system("clear"); // FOR LINUX
  vector<string> screenOut(lastRow_ + 1);

  char panel = 0;

  for (screenIt_t s_it = screen_.begin(); s_it != screen_.end(); ++s_it) {
    panelIt_t p_it = (*s_it).begin();
    for (panelIt_t scrOut_it = screenOut.begin(); scrOut_it != screenOut.end(); ++scrOut_it) {
      try {
        // Append panel string plus padding
        (*scrOut_it) += ((*p_it) + string(w_[panel] - (*p_it).length(), ' ') + "  ");
      }
      catch (const length_error& le) {
        (*scrOut_it) += ((*p_it) + "  ");
      }
      ++p_it;
    }
    ++panel;
  }

  // Output each row of the screen
  for (panelIt_t p_it = screenOut.begin(); p_it != screenOut.end(); ++p_it)
    cout << *p_it << endl;

  // Output stream after panels
  for (panelIt_t st_it = stream_.begin(); st_it != stream_.end(); ++st_it)
    cout << *st_it << endl;
}

void ConsoleDisplay::write(const unsigned char panel,
                           const unsigned char row,
                           const string& str)
{
  if (panel >= p_)
    return;
  else if (row >= h_)
    return;
  else if (w_[panel] < (screen_[panel][row].length() + str.length()))
    return;
  else
    screen_[panel][row] += str;

  if (lastRow_ < row)
    lastRow_ = row;
}

void ConsoleDisplay::write(const unsigned char panel, const string& str)
{
  if (p_ <= panel)
    return;
  else if (str.length() > w_[panel])
    return;

  char row = 0;
  panelIt_t p_it = screen_[panel].begin();
  while ((p_it != screen_[panel].end()) && (!(*p_it).empty())) {
    ++p_it;
    ++row;
  }

  if (h_ <= row)
    return;

  (*p_it) += str;

  if (lastRow_ < row)
    lastRow_ = row;
}

void ConsoleDisplay::write(const string& str)
{
  stream_.push_back(str);
}
