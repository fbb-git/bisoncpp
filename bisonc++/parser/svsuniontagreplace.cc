#include "parser.ih"

bool Parser::svsUnionTagReplace(int nElements, Block &block,AtDollar 
                                const &atd, char const *suffix)
{
    block.replace(atd.pos(), atd.length(), 
            svsElement(nElements, atd.nr()) + "." + atd.tag() + suffix);

    return false;
}
