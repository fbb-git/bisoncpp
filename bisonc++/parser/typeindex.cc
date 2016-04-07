#include "parser.ih"

    // static
int Parser::typeIndex(string const &typeName) 
{
    return typeName.empty() ?       0   :
            typeName == s_stype ? 1   :
                                    2;
}
