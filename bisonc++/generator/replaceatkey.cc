#include "generator.ih"

void Generator::replaceAtKey(string &line, size_t pos) const
{
    for (auto &atKey: s_at)
    {
        if (line.find(atKey.key, pos) == pos)
        {
            line.replace(pos, atKey.size, (this->*atKey.function)());
            return;
        }
    }
}
