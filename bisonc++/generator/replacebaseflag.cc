#include "generator.ih"

void Generator::replaceBaseFlag(string &line) const
{
    size_t pos = line.length();

    while ((pos = line.rfind(s_atFlag, pos)) != string::npos)   // found \@
    {
        auto iter = find(line, pos, s_at);

        if (iter != s_at.end())
            line.replace(pos, iter->size, (this->*iter->function)());
    }
}
