#ifndef INCLUDED_SPSEMBASE_
#define INCLUDED_SPSEMBASE_

#include "../sembase/sembase.h"

class spSemBase: public std::shared_ptr<SemBase>
{
    public:
        template <typename Type>
        spSemUnion(Type *obj);

        template <typename Type>
        Type const &as() const;
};
        
template <typename Type>
inline spSemUnion::spSemUnion(Type *obj)
:
    std::shared_ptr<SemBase>(obj)
{}

template <typename Type>
inline Type const &spSemUnion::as() const
{
    return dynamic_cast<Type &>(*this);
}

#endif
