#include "parser.ih"

Parser::SemTag Parser::semTagDIP(size_t nElements, int idx, 
                                 string const &typeTag) const
{
    if (idx > static_cast<int>(nElements))      // idx too large already 
        return UNTYPED;                         // resulted in an emsg
        
    if (idx < 0)
        return TYPEIGNORED;
                                                            // polymorphic
    if (d_polymorphic.find(typeTag) != d_polymorphic.end()) // type specified
        return TYPED;

    noSemanticTag(typeTag);

    return UNTYPED;
}

