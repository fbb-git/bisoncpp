#include "parser.ih"

void Parser::setClassName()
{
    if (d_className.size())
        lineMsg() << "%class-name multiply specified" << err;
    else
        d_className = d_scanner.YYText();
}
