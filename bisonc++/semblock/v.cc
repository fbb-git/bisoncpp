#include "sembool.ih"

SemBase *SemBool::v_clone() const
{
    return new SemBool(*this);
}

bool SemBool::v_logic() const
{
    return d_logic;
}
