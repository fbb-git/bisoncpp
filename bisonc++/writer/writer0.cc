#include "writer.ih"

Writer::Writer(std::string const &baseclass, Rules const &rules)
:
    d_out(0),
    d_baseclass(baseclass),
    d_rules(rules)
{
    if (Arg::instance().option(0, "thread-safe"))
        s_threadConst = "const ";
}

