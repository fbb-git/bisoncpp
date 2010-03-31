#ifndef _INCLUDED_SYMTAB_
#define _INCLUDED_SYMTAB_

#include <map>
#include <string>

#include "../symbol/symbol.h"
#include "../terminal/terminal.h"
#include "../nonterminal/nonterminal.h"

    // The symbol table holds the information about all symbols. It can be
    // queried to inspect whether it already contains an element, and it can 
    // store an element. Elements are strings, produced by the reader,
    // representing terminal or non-terminal symbols.
    // I only need one symbol table. Since many classes require access to the
    // names of the symbols the symtab is made into a Singleton. 

class Symtab: private std::map<std::string, Symbol *>
{
    typedef std::map<std::string, Symbol *> Base;

    public:
        typedef Base::value_type value_type;

        Symbol *lookup(std::string const &symbol);  // req'd for STL
        using Base::insert;                         // only map-members used
        using Base::find;
        using Base::erase;
};

        
#endif

