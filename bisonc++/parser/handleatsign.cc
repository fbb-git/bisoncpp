#include "parser.ih"

// We're at a @ character at position idx. @ should be followed by a number,
// @1, @2, ... etc. @<x> is the number of the element of a production rule
// The @-return value is not specified in bison's documentation. Is it not
// used? Using the @ feature implies lsp-needed, which is set by implication

void Parser::handleAtSign(size_t pos, size_t nElements, Block &block) 
{
    int idx;                // extract the index, determine its length
    size_t replaceSize = 1 + extractIndex(&idx, pos + 1);

    ostringstream os;
    os << s_locationValueStack << "[" << indexToOffset(idx, nElements) << "]";

    block.replace(pos, replaceSize, os.str());

    if (!d_lspNeeded)
    {
        msg() << "@ used in the action block at line " << 
                block.line() <<
                ": %lsp-needed forced" << warning;
        d_lspNeeded = true;
    }
}






