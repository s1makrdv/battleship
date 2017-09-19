#ifndef CONSOLEDISPLAY_H
#define CONSOLEDISPLAY_H

#include <vector>
#include <string>

class ConsoleDisplay
{
  public:
    ConsoleDisplay(const char widths_[], const char panels, const char height);

    void clear();
    void refresh();
    void write(const std::string& str);
    void write(const unsigned char panel, const std::string& str);
    void write(const unsigned char panel, const unsigned char row, const std::string& str);

  private:
    const std::vector<char> widths_;
    const char height_, panels_;
    char lastRow_;
    std::vector< std::vector<std::string> > screen_;
    std::vector<std::string> stream_;
};

#endif // CONSOLEDISPLAY_H
