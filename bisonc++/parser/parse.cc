#include "parser.ih"

void Parser::parse() 
{
    parseDeclarations();

    parseGrammar();

    if (!d_rules.nProductions())
        msg() << "No production rules found" << fatal;

    setAccessorVariables();

    d_rules.augmentGrammar(d_symtab.lookup(d_rules.startRule()));
}
