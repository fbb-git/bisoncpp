#include "parser.ih"

bool Parser::svsPolyReplace(int nElements, Block &block,AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = productionTag(atd.nr());        // get the element's tag

    if (tag == s_stype)
        tag.clear();

    block.replace(atd.pos(), atd.length(), 
                svsElement(nElements, atd.nr()) +
                (
                    tag.empty() ? 
                        ""s 
                    : 
                        ".get<Tag__::" + tag + ">()"
                ) + suffix);

    return false;
}
