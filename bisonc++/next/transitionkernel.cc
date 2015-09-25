#include "next.ih"

ostream &Next::transitionKernel(ostream &out) const
{
    checkRemoved(out);

    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

//    out << "On " << pSymbol() << " to state " << 
    out << "  On ";
    Symbol const *ps = pSymbol();
    if (ps)
        out << ps;
    else
        out << "????";

    out << " to state " <<
          d_next << " with (";
//        static_cast<int>(d_next) << " with (";

    copy(d_kernel.begin(), d_kernel.end(), 
         ostream_iterator<size_t>(out, " "));

    return out << ")";
}
