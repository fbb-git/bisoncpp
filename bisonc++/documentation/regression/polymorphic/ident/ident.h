#ifndef _INCLUDED_IDENT_
#define _INCLUDED_IDENT_

#include <string>

#include "../base/base.h"

class Ident: public Base
{
    std::string d_ident;

    public:
        Ident(std::string const &id);
        virtual Base *clone() const;
        string const &id() const;           // directly access the name.
        virtual ostream &insert(ostream &os) const;
};

inline Ident::Ident(std::string const &id)
:
    d_ident(id)
{}

inline Base *Ident::clone() const 
{
    return new Ident(*this);     // default CopyCons is ok.
}

inline  string const &Ident::id() const
{
    return d_ident;
}

inline ostream &Ident::insert(ostream &out) const
{
    return out << d_ident;
}

#endif





