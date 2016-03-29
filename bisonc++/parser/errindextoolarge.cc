#include "parser.ih"

bool Parser::errIndexTooLarge(AtDollar const &atd, int elements) const
{
    if (not atd.stackElement())     // when referring to $$ or @@
        return false;

    int nElements = nComponents(elements);

    if (atd.nr() <= nElements)
        return false;

    emsg << "rule " << &d_rules.lastProduction() << ":\n"
                "\t\t" << atd.text() << ": index " << atd.nr() << 
                " exceeds # components before "
                "the action block (" << nElements << ")." << endl;

    return true;
}
