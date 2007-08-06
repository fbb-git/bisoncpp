#include "block.ih"

void Block::open(size_t lineno, string const &source)
{
    if (d_count == 0)       // assign line if no braces were open yet
    {
        clear();
        ++d_count;
        this->string::operator=("{");
        d_line = lineno;
        d_source = source;
    }
}
