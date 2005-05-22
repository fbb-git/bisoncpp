#include "generator.ih"

void Generator::filter(istream &in, ostream &out) const
{
    while (getline(in, d_line))
    {
        if (d_line.find("$insert") == 0)
        {
            insert(out);
            continue;
        }

        while (true)
        {
            unsigned pos = d_line.find_last_of("@");
            if (pos == string::npos)
                break;
            d_line.replace(pos, 1, d_parser.className());
        }

        out << d_line << endl;
    }
}
