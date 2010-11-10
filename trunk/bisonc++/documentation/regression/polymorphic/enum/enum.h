#ifndef _INCLUDED_ENUM_
#define _INCLUDED_ENUM_

#include "../base/base.h"

class Enum: public Base
{
    public:
        enum Value
        {
            ZERO,
            ONE,
            TWO
        };

    private:
        Value d_value;

    public:
        Enum(Value v);
        virtual Base *clone() const;
        Value value() const;                // directly access the value
        virtual ostream &insert(ostream &os) const;
};

inline Enum::Enum(Value v)
:
    d_value(v)
{}

inline Base *Enum::clone() const 
{
    return new Enum(*this);
}

inline Enum::Value Enum::value() const
{
    return d_value;
}

inline ostream &Enum::insert(ostream &out) const
{
    return out << d_value;
}

#endif


