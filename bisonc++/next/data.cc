#include "next.hh"

ostream &(Next::*Next::s_insertPtr)(ostream &out) const = &Next::transition;
