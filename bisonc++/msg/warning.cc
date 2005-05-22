#include "msg.ih"

void warning(ostream &out)
{
    ++Msg::s_warnCount;

    ostringstream &os = dynamic_cast<ostringstream &>(out);

    Msg::s_out << Msg::s_warning << os.str() << endl;

    if (!Msg::s_display || Msg::s_out.rdbuf() == Msg::s_info.rdbuf())
        return;

    Msg::s_info << Msg::s_warning << os.str() << endl;
}

