#ifndef _INCLUDED_MSG_
#define _INCLUDED_MSG_

#include <sstream>
#include <ostream>
#include <fstream>
#include <string>

void info(std::ostream &out);
void spool(std::ostream &out);
void warning(std::ostream &out);
void err(std::ostream &out);
void fatal(std::ostream &out);
std::ostringstream &msg();
std::ostringstream &lineMsg();

void operator<<(std::ostream &ostrstream, void (*)(std::ostream &));

class Msg
{
    friend void err(std::ostream &out);
    friend void spool(std::ostream &out);
    friend void info(std::ostream &out);
    friend void warning(std::ostream &out);
    friend void fatal(std::ostream &out);

    friend std::ostringstream &msg();
    friend std::ostringstream &lineMsg();

    static unsigned s_line;    
    static char const *s_warning;
    static unsigned s_warnCount;
    static unsigned s_count;
    static unsigned s_maxCount;
    static unsigned const s_defaultMaxCount = 10;
    static std::ostringstream s_msg;
    static std::ostream s_out;
    static std::ostream s_info;
    static std::ofstream s_fout;
    static bool s_display;

    public:
        static bool display()
        {
            return s_display;
        }

        static void open(std::ifstream &in, std::string const &name);
        static void open(std::ofstream &out, std::string const &name);

        static bool setDisplay(bool mode);

        static void setOstream(std::string const &name);

        static void setLine(unsigned linenr)
        {
            s_line = linenr;
        }            
        static void setWarning(char const *pre = "[Warning] ")
        {
            s_warning = pre;
        }

        static void setMaxCount(unsigned maxCount)
        {
            s_maxCount = maxCount;
        }
        static unsigned count()
        {
            return s_count;
        }
        static bool errors()
        {
            return s_count;
        }
        static unsigned warnings()
        {
            return s_warnCount;
        }
        static std::streambuf *setInfoBuf(std::streambuf *newBuffer,
                                          bool display = true);

        static std::streambuf *infoToWarning()
        {
            return setInfoBuf(s_out.rdbuf());
        }
};

#endif



