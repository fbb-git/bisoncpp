#include "parser.ih"

void Parser::noDefaultTypeWarning()
{
    if (d_unionDeclared)
        lineMsg() << "In production rule \n"<< 
                            "\t`" << &d_rules.lastProduction() << " '\n"
                            "\t`" << d_rules.name() << "' has no default "
                                        "($$) type-association" << warning;
}
