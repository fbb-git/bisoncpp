#include "msg.ih"

void Msg::open(std::ofstream &out, std::string const &name)
{
    out.open(name.c_str());

    if (!out)
        msg() << "Can't write `" << name << "'" << fatal;
}
