#include "msg.ih"

char const *Msg::s_warning = "[Warning] ";
bool Msg::s_display;
unsigned Msg::s_line;
unsigned Msg::s_warnCount;
unsigned Msg::s_count;
unsigned Msg::s_maxCount = s_defaultMaxCount;
ostringstream Msg::s_msg;
ostream Msg::s_out(cout.rdbuf());
ostream Msg::s_info(cout.rdbuf());
ofstream Msg::s_fout;

