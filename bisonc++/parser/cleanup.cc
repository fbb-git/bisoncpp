#include "parser.ih"

void Parser::cleanup()
{
    d_rules.clearLocations();   // locations aren't required anymore

    if (!d_rules.hasRules() || !d_rules.nProductions())
        fmsg << "No production rules" << noid;

    emsg.setTag("error");

    if (emsg.count())       // Terminate if parsing produced errors. 
        throw 1;

    d_options.setAccessorVariables();

    d_rules.augmentGrammar(d_symtab.lookup(d_rules.startRule()));

    d_options.setVerbosity();   // prepare Msg for verbose output
                                // (--verbose, --construction) 

    d_options.showFilenames();
                            // shows the verbosity-filename, otherwise 
                            // independent of the verbosity setting

}




