#include "block.ih"

void Block::open(size_t lineno, string const &source)
{
    if (d_count)            // existing block ?
        *this += "{";       // add open curly bracket to the block's code
    else
    {                       // assign line if no braces were open yet
        clear();
        this->string::operator=("{");
        d_lineNr = lineno;
        d_source = source;
    }
        
    ++d_count;                  // here, as clear() will reset d_count
}
