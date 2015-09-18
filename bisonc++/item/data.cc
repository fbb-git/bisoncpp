#include "item.hh"

ostream &(Item::*Item::s_insertPtr)(ostream &out) const = &Item::plainItem;
