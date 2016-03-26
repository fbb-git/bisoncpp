#include "atdollar.ih"

    // $<ID>-NR, ($<ID>-NR),
    // $<ID>-NR.   

AtDollar::AtDollar(Type type, size_t blockPos, size_t lineNr, 
                    string const &text, string const &tag, int nr)
:
    d_type(type),
    d_lineNr(lineNr),
    d_pos(blockPos),
    d_length(text.length()),
    d_text(text),
    d_tag(tag),
    d_nr(nr)
{
    suffixAndMember();
}
