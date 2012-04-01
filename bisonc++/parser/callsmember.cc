#include "parser.ih"

    // callsMember does not recognize constructions like ($$).

bool Parser::callsMember(Block const &block, size_t pos) const
{
    if (block.length() == pos + 1)  // nothing trails the $:  no member called
        return false;

                                    // locate the next non-blank char
    pos = block.find_first_not_of(" \t\n", pos + 1);

    if (pos == string::npos)        // none found, so no member called
        return false;
                                    // member is called (replace $$ by
    return block[pos] == '.';       // d_val__) if $$. is used
}
