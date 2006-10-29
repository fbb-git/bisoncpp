#include "next.ih"

ostream &(Next::*Next::s_insert[])(ostream &out) const =
{
    &Next::insertStd,
    &Next::insertStd,
    &Next::insertExt,
};
