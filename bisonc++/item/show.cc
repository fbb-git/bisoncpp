#include "item.ih"

void Item::show() const
{
    msg() << d_production << ", dot: " << d_dot << ", LA: " << 
            d_lookahead << info;
}
