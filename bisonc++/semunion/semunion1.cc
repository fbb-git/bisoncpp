#include "semunion.ih"

SemUnion::SemUnion(SemUnion const &other)
{
    switch (d_index = other.d_index)
    {
        case INT:
            d_int = other.d_int;
        break;

        case BOOL:
            d_bool = other.d_bool;
        break;

        case STRING:
            new (&d_str) std::string(other.d_str);
        break;

        case BLOCK:
            new (&d_block) Block(other.d_block);
        break;

        case TERMINAL:
            d_terminal = other.d_terminal;
        break;

        case SYMBOL:
            d_symbol = other.d_symbol;
        break;

        default:
        break;
    }
}

