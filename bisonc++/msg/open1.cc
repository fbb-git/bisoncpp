#include "msg.ih"

void Msg::open(std::ifstream &in, std::string const &name)
{
    in.open(name.c_str());

    if (!in)
        msg() << "Can't read `" << name << "'" << fatal;
}
