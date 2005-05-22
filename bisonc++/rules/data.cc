#include "rules.ih"

unsigned Rules::s_nExpectedConflicts;
unsigned Rules::s_acceptProductionNr;
    
    // <none>: default inheritedTerminal value in states in which no 
    // input has as yet been read.
Terminal Rules::s_errorTerminal("error",  "_error_", 
                                                Symbol::SYMBOLIC_TERMINAL);

Terminal Rules::s_defaultTerminal("default", "_default_",
                                                Symbol::SYMBOLIC_TERMINAL);

Terminal Rules::s_eofTerminal("EOF",  "_EOF_",  Symbol::SYMBOLIC_TERMINAL);
