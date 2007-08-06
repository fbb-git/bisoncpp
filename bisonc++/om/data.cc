#include "om.ih"

OM::InsType OM::s_type = OM::STD;
OM::InsType OM::s_saved = OM::STD;

ostream &(*OM::s_manipulator[])(ostream &out) =
{
    &raw,
    &std,
    &ext,
    &spec,
    &std,
    &symtype
};
