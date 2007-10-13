#include "item.ih"

ostream &(Item::*Item::s_insertPtr)(ostream &out) const = &Item::plainItem;
