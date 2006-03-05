#include "parser.ih"

// pos points to $ in what must be $<type>i

bool Parser::explicitElement(unsigned pos, unsigned nElements) 
{
    string explicitType;        // extract the explicit type
    unsigned length = 1 + extractType(&explicitType, pos + 1);

    int idx;                // extract the index, determine its length
    length  += extractIndex(&idx, pos + length);

    string const &idxType = d_rules.sType(idx); // get the idx'th default type

    if (idx > static_cast<int>(nElements))      // $i refers beyond this rule
        lineMsg() << "In  " << d_rules.name() << 
                    ": $<" << idxType << ">" << idx << 
                    " used, but the rule has only " << 
                    nElements << " elements" << err;
    else if 
    (
        !idxType.length()                       // idx'th element has no type
        && 
        explicitType.length()                   // and explicit type was used
    )
    {            
        if (idx > 0 || !d_negativeDollarIndices)
            lineMsg() << "Using $<" << explicitType << ">" << idx << 
                " for "<< (idx <= 0 ? "type-indeterminable" : "") <<
                " element $" << idx << " in `" << 
                d_rules.name() << "'" << warning;
    }

    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << 
                                  "]";
    string replacement = os.str();

    string const &typeToUse = explicitType.empty() ? idxType : explicitType;

    if (typeToUse.length())
        replacement += "." + typeToUse;

    d_block.replace(pos, length, replacement);

    return false;           // this is not a $$ variant.
}
