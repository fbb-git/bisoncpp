#include "production.ih"

std::ostream &operator<<(std::ostream &out, Production const &production)
{
    out << production.lhs()->name() << " ->";

    if (!production.size())
        return out <<  "    <empty>";

    for 
    (
        Production::const_iterator sym = production.begin();
            sym != production.end();
                ++sym
    )
        Production::showElement(out, *sym);
    
    return out;
}


