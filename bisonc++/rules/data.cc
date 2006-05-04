#include "rules.ih"

unsigned Rules::s_nExpectedConflicts;
unsigned Rules::s_acceptProductionNr;

Symbol *Rules::s_startSymbol;
    
Terminal Rules::s_errorTerminal("error",  "_error_", 
                                                Symbol::SYMBOLIC_TERMINAL);

Terminal Rules::s_eofTerminal("EOF",  "_EOF_",  Symbol::SYMBOLIC_TERMINAL);


