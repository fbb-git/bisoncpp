#include "msg.ih"

void err(ostream &out)
{
    ostringstream &os = dynamic_cast<ostringstream &>(out);

    Msg::s_out << "[Error " << ++Msg::s_count << "] " << os.str() << endl;

    if (Msg::s_display && Msg::s_out.rdbuf() != Msg::s_info.rdbuf())
        Msg::s_info << "[Error " << Msg::s_count << "] " << os.str() << endl;

    if (Msg::s_count > Msg::s_maxCount)
        msg() << "More than " << Msg::s_maxCount << " errors encountered." << 
                fatal;
}
