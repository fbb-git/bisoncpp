#include "stateitem.ih"

ostream &(StateItem::*StateItem::s_insert[])(ostream &out) const =
{
    &StateItem::insertStd,
    &StateItem::insertStd,
    &StateItem::insertExt,
};
