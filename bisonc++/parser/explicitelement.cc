#include "parser.ih"

// pos points to $ in what must be $<type>i

bool Parser::explicitElement(size_t pos, size_t nElements) 
{
    string explicitType;        // extract the explicit type
    size_t length = 1 + extractType(&explicitType, pos + 1);

    int idx;                // extract the index, determine its length
    length  += extractIndex(&idx, pos + length);

    string const &idxType = d_rules.sType(idx); // get the idx'th default type


    if (!d_unionDeclared)               // no %union: no explicit types
        lineMsg() << "No %union declaration: can't resolve $<" << 
            explicitType << ">" << idx << " for element $" << idx << 
            " in `" << d_rules.name()  << warning;

                                        // $i refers beyond this rule
    else if (idx > static_cast<int>(nElements))      
        lineMsg() << "In  " << d_rules.name() << 
                    ": $<" << explicitType << ">" << idx << 
                    " used, but the rule has only " << 
                    nElements << " elements" << warning;

    else if                                     
    (
        !idxType.length()               // idx'th element has no type
        && 
        explicitType.length()           // but explicit type was used
    )
    {            
        if 
        (                               // and either:
            idx > 0                     // a positive index
            || 
            !d_negativeDollarIndices    // or don't accept indices <= 0
        )                             
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
