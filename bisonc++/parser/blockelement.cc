#include "parser.ih"

unsigned Parser::blockElement(string *replacement, unsigned pos, 
                                unsigned nElements) 
{
    int idx;                // extract the index, determine its length
    unsigned length  = extractIndex(&idx, pos);


    string explicitType;        // extract an explicit type, if specified
    length += extractType(&explicitType, pos + length);

    string const &ownType = d_rules.sType(idx);

    if (d_rules.sType().length())
    {
        if (!explicitType.length() && idx < 0)
            lineMsg() << "cannot determine default type of $" << 
                                    idx << ", none used" << warning;
    
        if (!explicitType.length() && !ownType.length())
            lineMsg() << "$" << idx << " of `" << d_rules.name() << 
                         "' has no default type-association" << warning;
    }
        
    string const &typeToUse = explicitType.empty() ? ownType : explicitType;

    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << 
                                  "]";
    *replacement = os.str();

    if (typeToUse.length())
        *replacement += "." + typeToUse;

    return length;
}
