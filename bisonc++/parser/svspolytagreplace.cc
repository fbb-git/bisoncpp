#include "parser.ih"

bool Parser::svsPolyTagReplace(int nElements, Block &block,AtDollar 
                                const &atd, char const *suffix)
{
    block.replace(atd.pos(), atd.length(), 
            svsElement(nElements, atd) + 
                            ".get<Tag__::" + atd.tag() + ">()" +suffix);
    return false;
}
