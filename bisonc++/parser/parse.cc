#include "parser.ih"

void Parser::parse() 
{
    parseDeclarations();

    parseGrammar();

    if (!d_rules.nProductions())
        msg() << "No production rules found" << fatal;

    msg() << "\n"
            "This grammar uses " << Terminal::nActive() << 
            " terminal tokens\n" << info;

    setAccessorVariables();

    d_rules.augmentGrammar(d_symtab.lookup(d_rules.startRule()));
}
