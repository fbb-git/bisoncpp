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
            unsigned token = d_scanner.lex();
            Iterator it = s_action.find(token);

            if (it != s_action.end())
                (this->*it->second)();
            else
                junk();
        }
    }
    catch (int ok)
    {}

    // at the end, inspect all nonterminals. if there are any undetermined
    // nonterminals left, change them into true nonterminals.
    d_rules.setNonTerminalTypes();
}



