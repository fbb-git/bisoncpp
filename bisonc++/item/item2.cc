#include "item.ih"

Item::Item(Item const *item, unsigned dot)
:
    d_production(item->d_production),
    d_dot(dot),
    d_lookahead(item->d_lookahead)
{
//    cout << "ITEM CONSTRUCTED:\n"
//            "   production = " << d_production << "\n" <<
//            "   dot = " << d_dot << 
//            " LA in = " << item->d_lookahead << 
//            " LA out = " << d_lookahead << endl;
}
