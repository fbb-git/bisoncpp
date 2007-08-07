#include "parser.ih"

void Parser::setNameSpace()
{
    if (d_nameSpace.size())
        lineMsg() << "%namespace multiply specified" << err;
    else
        d_nameSpace = d_scanner.YYText();
}
