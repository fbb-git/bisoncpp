#include "parser.ih"

void Parser::noDefaultTypeWarning()
{
    wmsg << "production rule \n"<< 
            "\t`" << &d_rules.lastProduction() << " ':\n"
            "\tno auto type for `" << d_rules.name() << "'"
            " ($$)" << endl;
}
