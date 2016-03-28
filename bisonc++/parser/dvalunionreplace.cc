#include "parser.ih"

bool Parser::dvalUnionReplace(Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = productionTag(atd.nr());        // get the element's tag

cerr << "dvalueunionreplace tag = `" << tag << "', rule: `" << d_rules.sType()
<< "'\n";

    block.replace(atd.pos(), atd.length(), 
                s_semanticValue + (tag.empty() ? ""s : "." + tag) + suffix);

    return block.assignment();
}
