#include "generator.ih"

void Generator::productionInfo(ostream &out) const
{
    vector<Production const *> const &productions = d_rules.productions();

    out << "\n"
            "// Productions Info Records:\n" <<
            "PI s_productionInfo[] = \n"
            "{\n"
            "     {0, 0}, // not used: reduction values are negative\n";

    for
    (
        vector<Production const *>::const_iterator prodIter = 
                                                    productions.begin();
            prodIter !=  productions.end();
                prodIter++
    )
    {
        NonTerminal const *np = NonTerminal::downcast((*prodIter)->lhs());
        out << "     {" << np->nr() << ", " << 
            (*prodIter)->size() << "}, // " << *prodIter << "\n";
    }

    out << "};\n";
}







