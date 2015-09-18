#include "stateitem.hh"

ostream &(StateItem::*StateItem::s_insertPtr)(ostream &out) const = 
                                                        &StateItem::plainItem;
