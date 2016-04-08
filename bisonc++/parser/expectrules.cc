#include "parser.ih"

void Parser::expectRules()
{
    d_options.setParsingOptions();

        // by default $$ = $1 actions are added when there's no action block.
    if (d_options.defaultActions().value == Options::UNKNOWN)
        d_options.setDefaultAction("std", "", 0);

    d_scanner.clearBlock();

    Terminal::resetPrecedence();    // Incremented terminal priority must be
                                    // reset to 0: any terminal char-tokens 
                                    // seen below in the rules must again
                                    // receive the initial (0) priority

    // at the end, inspect all nonterminals. if there are any undetermined
    // nonterminals left, change them into true nonterminals.
    d_rules.setNonTerminalTypes();
}
