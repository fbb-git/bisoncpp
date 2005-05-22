#include "parser.ih"

void Parser::parse() 
{
    parseDeclarations();

    parseGrammar();

    setAccessorVariables();

    d_rules.augmentGrammar(d_symtab.lookup(d_rules.startRule()));
}
