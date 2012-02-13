#include "parser.ih"

// pos points to $ in what must be $<type>i

bool Parser::explicitElement(size_t pos, int nElements, Block &block) 
{
    string explicitType;        // extract the explicit type
    size_t length = 1 + extractType(&explicitType, pos + 1, block);

    int idx;                // extract the index, determine its length
    length  += extractIndex(&idx, pos + length);

    string const &idxType = d_rules.sType(idx); // get the idx'th default type

    size_t ruleElements = nComponents(nElements);

    if (!d_unionDeclared)               // no %union: no explicit types
        wmsg << "No %union declaration: can't resolve $<" << 
            explicitType << ">" << idx << " for element $" << idx << 
            " in `" << d_rules.name()  << endl;

                                        // $i refers beyond this rule
    else if (idx > static_cast<int>(ruleElements))
        emsg << "In  " << d_rules.name() << 
                ": $<" << explicitType << ">" << idx << 
                " used, but the rule has only " << 
                ruleElements << " elements" << endl;
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
            wmsg << "Using $<" << explicitType << ">" << idx << 
                " for "<< (idx <= 0 ? "type-indeterminable" : "") <<
                " element $" << idx << " in `" << 
                d_rules.name() << "'" << endl;
    }

    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << 
                                  "]";
    string replacement = os.str();

    string const &typeToUse = explicitType.empty() ? idxType : explicitType;

    if (typeToUse.length())
        replacement += "." + typeToUse;

    block.replace(pos, length, replacement);

    return false;           // this is not a $$ variant.
}

