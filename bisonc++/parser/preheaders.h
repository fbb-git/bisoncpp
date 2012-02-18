#ifndef _INCLUDED_PREHEADERS_H_
#define _INCLUDED_PREHEADERS_H_

#include <string>
#include <vector>
#include <memory>

#include <bobcat/arg>
#include <bobcat/string>

#include "../semstring/semstring.h"
#include "../sembool/sembool.h"
#include "../semsizet/semsizet.h"
#include "../semblock/semblock.h"

#include "../spsembase/spsembase.h"

#include "../rules/rules.h"
#include "../symtab/symtab.h"

class Terminal;

//namespace FBB
//{
//
//    // PTag is used by the parser as a semantic return value when processing
//    // productionElements. When processing series of production elements, PTag
//    // allows the parser to insert inner-blocks as pseudo nonterminals.
//struct PTag
//{
//    enum Tags
//    {
//        NONE,
//        BLOCK,
//        TERMINAL,
//        SYMBOL
//    };
//
//    Tags tag;
//
//    Block block;
//    Terminal *terminal;
//    Symbol *symbol;
//
//    PTag();
//    PTag(Block const &block);
//    PTag(Terminal *terminal);
//    PTag(Symbol *symbol);
//};
//
//inline PTag::PTag()
//:
//    tag(NONE)
//{}
//
//inline PTag::PTag(Terminal *term)
//:
//    tag(TERMINAL),
//    terminal(term)
//{}
//
//inline PTag::PTag(Block const &blck)
//:
//    tag(BLOCK),
//    block(blck)
//{}
//
//inline PTag::PTag(Symbol *sym)
//:
//    tag(SYMBOL),
//    symbol(sym)
//{}
//
//}   // namespace FBB

#endif
