#include "atdollar.ih"

      // ${NR}, ${NR}. or @{NR}

AtDollar::AtDollar(Type type, 
                 size_t blockPos, size_t lineNr, std::string const &text,
                 int nr)
:
    d_type(type),
    d_lineNr(lineNr),
    d_pos(blockPos),
    d_length(text.length()),
    d_text(text),
    d_nr(nr)
{
    suffixAndMember();
}
