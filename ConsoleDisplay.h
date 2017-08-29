#ifndef CONSOLEDISPLAY_H
#define CONSOLEDISPLAY_H

#include <vector>
#include <string>

class ConsoleDisplay {
public:
	typedef std::vector<std::vector<std::string> >::iterator screenIt_t;
	typedef std::vector<std::string>::iterator panelIt_t;

	// Constructor
    ConsoleDisplay(const char w_[], const char panels, const char height);

	void clear();
	void refresh();
	void write(const std::string& str);
	void write(const unsigned char panel, const std::string& str);
	void write(const unsigned char panel, const unsigned char row, const std::string& str);

private:
    const std::vector<char> w_;
    const char h_, p_;
    char lastRow_;
    std::vector< std::vector<std::string> > screen_;
    std::vector<std::string> stream_;
};

#endif // CONSOLEDISPLAY_H
