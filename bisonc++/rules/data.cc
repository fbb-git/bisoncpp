#include "rules.ih"

size_t Rules::s_lastLineNr;
size_t Rules::s_nExpectedConflicts;
size_t Rules::s_acceptProductionNr;

Symbol *Rules::s_startSymbol;
    
Terminal Rules::s_errorTerminal("error",  "errTok__", 
                                                Symbol::SYMBOLIC_TERMINAL);

Terminal Rules::s_eofTerminal("EOF",  "EOF__",  Symbol::SYMBOLIC_TERMINAL);
