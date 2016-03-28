#include "atdollar.ih"

AtDollar::AtDollar(size_t blockPos, size_t lineNr, std::string const &text,
                    bool refByScanner)
:
    d_pos(blockPos),
    d_lineNr(lineNr),
    d_text(text),
    d_length(text.length()),
    d_refByScanner(refByScanner)
{
    switch (text[0])
    {
        case '$':
            setDollarPatterns();
        return;

        case '_':
            setRefPatterns();
        return;

        case '@':
            setAtPatterns();
        return;
    }
}
    


//      // ${NR}, ${NR}. or @{NR}
//
//AtDollar::AtDollar(Type type, 
//                 size_t blockPos, size_t lineNr, std::string const &text,
//                 int nr)
//:
//    d_type(type),
//    d_lineNr(lineNr),
//    d_pos(blockPos),
//    d_length(text.length()),
//    d_text(text),
//    d_nr(nr)
//{
//    suffixAndMember();
//}
