#include "parser.ih"

bool Parser::dvalPolyReplace(Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = productionTag(atd.nr());        // get the element's tag

    block.replace(atd.pos(), atd.length(), 
                s_semanticValue + 
                (
                    tag.empty() ? 
                        ""s 
                    : 
                        ".get<Tag__::" + tag + ">()"
                ) + suffix);

    return block.assignment();
}

