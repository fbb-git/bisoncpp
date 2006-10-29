#include "parser.ih"

// Read all percent symbols until we're at %%
// Each action is implemented in a separate function, see data.cc (s_action)
// for the association.
// The scanner MUST return percent tokens here. If not, there's an input
// error. 

void Parser::parseDeclarations() 
{
    try
    {
        while (true)
        {
            size_t token = d_scanner.lex();
            Iterator it = s_action.find(token);

            if (it != s_action.end())
                (this->*it->second)();
            else
                junk();
        }
    }
    catch (int ok)
    {}

    Terminal::resetPrecedence();      // Incremented terminal priority must be
                                    // reset to 0: any terminal char-tokens 
                                    // seen below in the rules must again
                                    // receive the initial (0) priority

    // at the end, inspect all nonterminals. if there are any undetermined
    // nonterminals left, change them into true nonterminals.
    d_rules.setNonTerminalTypes();
}



