#include "scanner.ih"

namespace
{
    pair<size_t/*unsigned*/, size_t/*unsigned*/> escapeChars[] = 
    {
        pair<char, size_t/*unsigned*/>('a', '\a'),
        pair<char, size_t/*unsigned*/>('b', '\b'),
        pair<char, size_t/*unsigned*/>('f', '\f'),
        pair<char, size_t/*unsigned*/>('n', '\n'),
        pair<char, size_t/*unsigned*/>('r', '\r'),
        pair<char, size_t/*unsigned*/>('t', '\t'),
        pair<char, size_t/*unsigned*/>('v', '\v'),
    };
    static size_t/*unsigned*/ const n = sizeof(escapeChars) / 
                              sizeof(pair<char, size_t/*unsigned*/>);

    class Find
    {
        size_t/*unsigned*/ d_key;
        public:
            Find(size_t/*unsigned*/ key)
            :
                d_key(key)
            {}
            bool operator()(pair<size_t/*unsigned*/, size_t/*unsigned*/> const &element) const
            {
                return element.first == d_key;
            }
    };
}


void Scanner::escape()
{
    d_number = find_if(escapeChars, escapeChars + n, Find(yytext[2]))->second;
}
