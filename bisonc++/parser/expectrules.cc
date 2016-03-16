#include "parser.ih"

void Parser::expectRules()
{
    inspectDirectives();

    d_scanner.clearBlock();

    Terminal::resetPrecedence();    // Incremented terminal priority must be
                                    // reset to 0: any terminal char-tokens 
                                    // seen below in the rules must again
                                    // receive the initial (0) priority

    // at the end, inspect all nonterminals. if there are any undetermined
    // nonterminals left, change them into true nonterminals.
    d_rules.setNonTerminalTypes();

// not shown in Bisonc++ 2.8.0:
//    lineMsg(imsg) << "Preamble (until %%) parsed" << endl;
}
