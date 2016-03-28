#include "atdollar.ih"

std::ostream &operator<<(std::ostream &out, AtDollar const &atd)
{
    out << "At line " << atd.d_lineNr << ", block pos. " << atd.d_pos <<
            ", length: " << atd.d_length << ": `" << 
            atd.text() << "' (Pattern = " << atd.d_pattern << ')';

    if (atd.d_tag.length())
        out << "; <" << atd.d_tag << '>';

    if (atd.d_nr == numeric_limits<int>::max())
        out << " $";
    else
        out << ' ' << atd.d_nr;

    if (atd.d_refByScanner)
        out << " (ref. by scanner)";

    return out;
}
