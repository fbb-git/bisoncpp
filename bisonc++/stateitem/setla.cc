#include "stateitem.ih"

void StateItem::setLA(LookaheadSet const &laSet)
{
    d_LA = laSet;
//    d_LA_enlarged = true;
}
