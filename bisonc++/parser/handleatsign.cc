#include "parser.ih"

// We're at a @ character at position idx. @ should be followed by a number,
// @1, @2, ... etc. @<x> is the number of the element of a production rule
// The @-return value is not specified in bison's documentation. Is it not
// used? Using the @ feature implies lsp-needed, which is set by implication

void Parser::handleAtSign(unsigned pos, unsigned nElements) 
{
    int idx;                // extract the index, determine its length
    unsigned replaceSize = 1 + extractIndex(&idx, pos + 1);

    ostringstream os;
    os << s_locationValueStack << "[" << indexToOffset(idx, nElements) << "]";

    d_block.replace(pos, replaceSize, os.str());

    if (!d_lspNeeded)
    {
        msg() << "@ used in the action block at line " << d_block.line() <<
                ": %lsp-needed forced" << warning;
        d_lspNeeded = true;
    }
}






