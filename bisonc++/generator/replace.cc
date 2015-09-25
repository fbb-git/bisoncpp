#include "generator.ih"

void Generator::replace(string &str, char ch, string const &replacement)
{
    size_t pos = 0;

    while (true)
    {
        pos = str.find(pos, ch);
        if (pos == string::npos)
            return;
        str.replace(pos, 1, replacement);
        pos += replacement.length();
    }
}
