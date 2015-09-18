#include "atdollar.hh"

      // ${NR}, ${NR}. or @{NR}

AtDollar::AtDollar(Type type, 
                 size_t blockPos, size_t lineNr, std::string const &text,
                 int nr, bool member)
:
    d_type(type),
    d_lineNr(lineNr),
    d_pos(blockPos),
    d_length(text.length() - member),
    d_text(text),
    d_nr(nr),
    d_member(member),
    d_stype(false)
{}
