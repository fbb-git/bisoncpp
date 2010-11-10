#include "terminal.ih"

size_t        Terminal::s_precedence;
set<size_t>   Terminal::s_valueSet;
size_t        Terminal::s_value = Terminal::INITIAL_SYMBOLIC_VALUE;
size_t        Terminal::s_maxValue;

char const *Terminal::s_association[] = 
{
    "",                   // UNDEFINED,
    "non-associative",    // NONASSOC,
    "left associative",   // LEFT,
    "right associative",  // RIGHT
};


ostream &(Terminal::*Terminal::s_insertPtr)(ostream &out) const =
                                                &Terminal::plainName; 
