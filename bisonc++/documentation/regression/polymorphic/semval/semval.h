#ifndef _INCLUDED_SEMVAL_
#define _INCLUDED_SEMVAL_

#include "../base/base.h"

class SemVal
{
    Base *d_bp;

    public:
        SemVal();                   // Never used by me, but needed to
                                    // enlarge the semantic value stack

        SemVal(Base *bp);           // Semval will own bp
        SemVal(SemVal const &other);
        ~SemVal();

        SemVal &operator=(SemVal const &other);

        Base const &base() const;

        template <typename Class>
        Class const &downcast();

    private:
        void copy(SemVal const &other);
        void destroy();
};

inline Base const &SemVal::base() const
{
    return *d_bp;
}

inline SemVal::SemVal()
:
    d_bp(0)
{}

inline SemVal::SemVal(Base *bp)
:
    d_bp(bp)
{}

inline SemVal::~SemVal()
{
    destroy();
}
       
inline SemVal::SemVal(SemVal const &other)
{
    copy(other);
}

inline SemVal &SemVal::operator=(SemVal const &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);        
    }
    return *this;
}

inline void SemVal::copy(SemVal const &other)
{
    d_bp = other.d_bp ? other.d_bp->clone() : 0;
}

inline void SemVal::destroy()
{
    delete d_bp;
}

template <typename Class>
inline  Class const &SemVal::downcast()
{
    return dynamic_cast<Class &>(*d_bp);
}

inline ostream &operator<<(ostream &out, SemVal const &obj)
{
    if (&obj.base())
        return out << obj.base();

    return out << "<0>";
}

#endif
