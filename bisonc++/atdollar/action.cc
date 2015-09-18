#include "atdollar.hh"

AtDollar::Action AtDollar::action() const
{
    if (d_nr == numeric_limits<int>::max())
        return d_id.length() ? TYPED_RETURN_VALUE : RETURN_VALUE;

    return d_id.length() ? TYPED_NUMBERED_ELEMENT : NUMBERED_ELEMENT;        
}
