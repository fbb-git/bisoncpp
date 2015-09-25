#include "nonterminal.ih"

size_t NonTerminal::s_counter;
size_t NonTerminal::s_number;
bool NonTerminal::s_unused;
bool NonTerminal::s_undefined;

ostream &(NonTerminal::*NonTerminal::s_insertPtr)(ostream &out) const =
                                                  &NonTerminal::plainName;
