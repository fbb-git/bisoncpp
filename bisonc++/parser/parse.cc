#include "parser.ih"

void Parser::parse() 
{
    if (d_arg.option(&d_preInclude, 'H'))
        setIncludeQuotes(&d_preInclude);
    
    if (d_arg.option(&d_implementationHeader, 'i'))
        setIncludeQuotes(&d_implementationHeader);
    
    if (d_arg.option(&d_scannerInclude, 's'))
        setIncludeQuotes(&d_scannerInclude);
    
    parseDeclarations();

    parseGrammar();

    if (!d_rules.nProductions())
        msg() << "No production rules found" << fatal;

    setAccessorVariables();

    d_rules.augmentGrammar(d_symtab.lookup(d_rules.startRule()));
}
