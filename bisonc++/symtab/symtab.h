#ifndef _INCLUDED_SYMTAB_
#define _INCLUDED_SYMTAB_

#include <unordered_map>
#include <string>

#include "../symbol/symbol.h"
#include "../terminal/terminal.h"
#include "../nonterminal/nonterminal.h"

    // The symbol table holds the information about all symbols. It can be
    // queried to inspect whether it already contains an element, and it can 
    // store an element. Elements are strings, produced by the reader,
    // representing terminal or non-terminal symbols.

class Symtab: private std::unordered_map<std::string, Symbol *>
{
    typedef std::unordered_map<std::string, Symbol *> Base;

    public:
        typedef Base::value_type value_type;

        Symbol *lookup(std::string const &symbol);  // req'd for STL
        using Base::insert;                         // only map-members used
        using Base::find;
        using Base::erase;
};

        
#endif

