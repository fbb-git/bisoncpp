#ifndef _INCLUDED_INT_
#define _INCLUDED_INT_

#include <ostream>
#include <string>

#include <bobcat/a2x>

#include "../base/base.h"

class Int: public Base
{
    int d_value;

    public:
        Int(std::string const &text);

    private:
        virtual std::ostream &v_insert(std::ostream &os) const;
};

inline Int::Int(std::string const &txt)
:
    d_value(FBB::A2x(txt))
{}

inline std::ostream &Int::v_insert(std::ostream &out) const
{
    return out << d_value;
}

#endif

