#include "parser.ih"

bool Parser::vspTagReplace(int nElements, Block &block,AtDollar const &atd, 
                           char const *suffix)
{
    if (checkExistingTag(atd))
    {
        ostringstream  replacement;
    
        replacement << s_semanticValueStack << "[" << 
                            indexToOffset(atd.nr(), nElements) << 
                            "].get<Tag__::" << atd.tag() << ">()" << suffix;
    
        block.replace(atd.pos(), atd.length(), replacement.str());
    }
    return false;
}
