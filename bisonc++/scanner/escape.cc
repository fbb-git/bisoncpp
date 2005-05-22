#include "scanner.ih"

namespace
{
    pair<unsigned, unsigned> escapeChars[] = 
    {
        pair<char, unsigned>('a', '\a'),
        pair<char, unsigned>('b', '\b'),
        pair<char, unsigned>('f', '\f'),
        pair<char, unsigned>('n', '\n'),
        pair<char, unsigned>('r', '\r'),
        pair<char, unsigned>('t', '\t'),
        pair<char, unsigned>('v', '\v'),
    };
    static unsigned const n = sizeof(escapeChars) / 
                              sizeof(pair<char, unsigned>);

    class Find
    {
        unsigned d_key;
        public:
            Find(unsigned key)
            :
                d_key(key)
            {}
            bool operator()(pair<unsigned, unsigned> const &element) const
            {
                return element.first == d_key;
            }
    };
}


void Scanner::escape()
{
    d_number = find_if(escapeChars, escapeChars + n, Find(yytext[2]))->second;
}
