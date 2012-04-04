#include "parser.ih"

// We're at a @ character, followed by a number, @1, @2, ... etc. @<x>. 
// The number is the element number  of a production rule
// The @-return value is not specified in bison's documentation. Is it not
// used? Using the @ feature implies lsp-needed, which is set by implication

void Parser::handleAtSign(Block &block, AtDollar const &atd, int nElements) 
{
    ostringstream os;
    os << s_locationValueStack << "[" << 
                                indexToOffset(atd.nr(), nElements) << "]";

    block.replace(atd.pos(), atd.length(), os.str());

    if (!d_options.lspNeeded())
    {
        wmsg << "@ used at line " << block.line() << ": %lsp-needed forced" << 
                endl;
        d_options.setLspNeeded();
    }
}






