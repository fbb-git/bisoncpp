#include "atdollar.hh"

    // $<ID>$ or $<ID>-?NR

AtDollar::AtDollar(Type type, size_t blockPos, size_t lineNr, 
                    string const &text, string const &id, int nr)
:
    d_type(type),
    d_lineNr(lineNr),
    d_pos(blockPos),
    d_length(text.length()),
    d_text(text),
    d_id(id.empty() ? "STYPE__" : id),
    d_nr(nr),
    d_member(false),
    d_stype(d_id == "STYPE__")
{}
