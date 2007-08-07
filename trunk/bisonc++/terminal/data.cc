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


ostream &(Terminal::*Terminal::s_insert[])(ostream &out) const =
{
    &Terminal::literal,
    &Terminal::standard,
    &Terminal::standard,
    &Terminal::special,
    &Terminal::srTable,  
};
