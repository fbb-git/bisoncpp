#include "parser.ih"

// We're at a @ character, followed by a number, @1, @2, ... etc. @<x>. 
// The number is the element number  of a production rule
// The @-return value is not specified in bison's documentation. Is is
// d_loc__. @@ is replaced by d_loc__

void Parser::handleAtSign(Block &block, AtDollar const &atd, int nElements) 
{
    if (errIndexTooLarge(atd, nElements))
        return;

    ostringstream os;
    if (atd.dollarDollar())
        os << s_locationValue;
    else
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






