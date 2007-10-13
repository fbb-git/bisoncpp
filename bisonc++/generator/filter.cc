#include "generator.ih"

void Generator::filter(istream &in, ostream &out) const
{
    Terminal::inserter(&Terminal::plainName);

    while (getline(in, d_line))
    {
        if (d_line.find("$insert") == 0)
        {
            insert(out);
            continue;
        }

        while (true)
        {
            size_t pos = d_line.rfind(s_baseFlag);
            if (pos == string::npos)
                break;
            d_line.replace(pos, s_baseFlagSize, d_parser.className());
        }

        out << d_line << endl;
    }
}
