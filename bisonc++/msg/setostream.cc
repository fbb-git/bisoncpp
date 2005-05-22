#include "msg.ih"

void Msg::setOstream(string const &name) 
{
    open(s_fout, name);

    s_out.rdbuf(s_fout.rdbuf());
}
