#include "stateitem.ih"

ostream &(StateItem::*StateItem::s_insertPtr)(ostream &out) const = 
                                                        &StateItem::plainItem;
