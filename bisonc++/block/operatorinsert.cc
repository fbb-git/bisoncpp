#include "block.ih"

std::ostream &operator<<(std::ostream &out, Block const &blk)
{
    out << '`' << static_cast<std::string>(blk) << "'\n";

    copy(blk.d_atDollar.rbegin(), blk.d_atDollar.rend(), 
            ostream_iterator<AtDollar>(out, "\n"));

    return out;
}
