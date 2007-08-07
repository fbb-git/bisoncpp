#include "item.ih"

ostream &(Item::*Item::s_insert[])(ostream &out) const =
{
    &Item::insertStd,
    &Item::insertStd,
    &Item::insertExt,
};
