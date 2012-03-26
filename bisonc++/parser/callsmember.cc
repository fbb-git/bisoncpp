#include "parser.ih"

bool Parser::callsMember(Block const &block, size_t pos)
{
    if (block.length() == pos + 1)  // no member if just using $$
        return false;

    pos = block.find_first_not_of(" \t\n", pos + 1);

    return pos != string::npos && block[pos] == '.';
}
