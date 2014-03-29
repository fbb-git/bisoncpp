#include "generator.ih"

void Generator::replaceAtKey(string &line, size_t pos) const
{
    for (auto &atKey: s_at)
    {
        if (line.find(pos, atKey.key) == 0)
        {
            line.replace(pos, atKey.size, (this->*atKey.function)());
            return;
        }
    }
}
