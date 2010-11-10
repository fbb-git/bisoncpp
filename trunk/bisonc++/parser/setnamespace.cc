#include "parser.ih"

void Parser::setNameSpace()
{
    if (d_nameSpace.size())
        lineMsg(emsg) << "%namespace multiply specified" << endl;
    else
        d_nameSpace = d_scanner.YYText();
}
