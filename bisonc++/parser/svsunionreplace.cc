#include "parser.ih"

bool Parser::svsUnionReplace(int nElements, Block &block,AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = productionTag(atd.nr());        // get the element's tag

    block.replace(atd.pos(), atd.length(), 
                svsElement(nElements, atd.nr()) +
                                (tag.empty() ? ""s : "." + tag) + suffix);

    return false;
}
