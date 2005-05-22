#include "terminal.ih"

ostream &Terminal::insert(ostream &out) const
{
    if ((d_literal)[0] == '\'')
        return out;

    out << d_literal << 
        setw(max(10 - static_cast<int>(d_literal.length()), 1)) << " " <<
        "(= " << d_value << ")";

    if (sType().length())
        out << " <" << sType() << ">";
    
    if (d_association != Terminal::UNDEFINED)
        out << ", " << Terminal::s_association[d_association];
    
    if (d_priority)
        out << ", prec: " << d_priority;
    
    return out << endl;
}
