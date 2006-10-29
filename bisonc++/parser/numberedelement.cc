#include "parser.ih"

// pos points to $ in what must be $i

bool Parser::numberedElement(size_t pos, size_t nElements) 
{
    int idx;                // extract the index, determine its length
    size_t length  = 1 + extractIndex(&idx, pos + 1);

    string const &idxType = d_rules.sType(idx);

    if (idx > static_cast<int>(nElements)) // $i refers beyond this rule
        lineMsg() << "In  " << d_rules.name() << 
                    ": $" << idx << " used, but the rule has only " << 
                    nElements << " elements" << err;
    else if (d_unionDeclared)
    {
        if (idx <= 0)                   // type of the $i can't be determined
        {                               // and indices <= 0 are not accepted
            if (!d_negativeDollarIndices)
                lineMsg() << "In " << d_rules.name() << 
                        ": cannot determine default type of $" << 
                        idx << warning;
        }
        else if (!idxType.length())     // or $i without type association
            lineMsg() << "$" << idx << " of `" << d_rules.name() << 
                         "' has no default type-association" << warning;
    }        

    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << "]";
    string replacement = os.str();

    if (idxType.length())
        replacement += "." + idxType;

    d_block.replace(pos, length, replacement);

    return false;           // this is not a $$ variant.
}
