#include "parser.ih"

void Parser::saveDollar1(Block &block, int offset)
{
    ostringstream out;

    out << s_semanticValue << " = " << s_semanticValueStack << '[' << 
            offset << "];\n";

    block.insert(0, out.str());
}
