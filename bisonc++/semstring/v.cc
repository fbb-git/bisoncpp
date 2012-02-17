#include "semstring.ih"

SemBase *SemString::v_clone() const
{
    return new SemString(*this);
}

string const &SemString::v_str() const
{
    return *this;
}
