#include "parser.ih"

void Parser::setClassName()
{
    if (d_className.size())
        lineMsg(emsg) << "%class-name multiply specified" << endl;
    else
        d_className = d_scanner.YYText();
}
