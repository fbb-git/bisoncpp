#include "parser.ih"

void Parser::newProduction() 
{
    installAction();                // `installAction()'
                                    // installs a pending action for
                                    // the last production rule
    d_rules.addProduction();

}

