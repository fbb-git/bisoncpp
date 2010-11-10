#include "next.ih"

ostream &(Next::*Next::s_insertPtr)(ostream &out) const = &Next::transition;
