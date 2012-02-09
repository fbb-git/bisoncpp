#include "scanner.ih"

namespace
{
    pair<size_t, size_t> escapeChars[] = 
    {
        pair<char, size_t>('a', '\a'),
        pair<char, size_t>('b', '\b'),
        pair<char, size_t>('f', '\f'),
        pair<char, size_t>('n', '\n'),
        pair<char, size_t>('r', '\r'),
        pair<char, size_t>('t', '\t'),
        pair<char, size_t>('v', '\v'),
    };
    static size_t const n = sizeof(escapeChars) / 
                              sizeof(pair<char, size_t>);

    class Find
    {
        size_t d_key;
        public:
            Find(size_t key)
            :
                d_key(key)
            {}
            bool operator()(pair<size_t, size_t> const &element) const
            {
                return element.first == d_key;
            }
    };
}


void Scanner::escape()
{
    d_number = find_if(escapeChars, escapeChars + n, Find(d_matched[2]))->second;
}
