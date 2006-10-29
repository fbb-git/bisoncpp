#include "stateitem.ih"

void StateItem::setChildren(vector<size_t> const &dep)
{
    copy(dep.begin(), dep.end(), back_inserter(d_child));
}
