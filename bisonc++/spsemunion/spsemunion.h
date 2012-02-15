#ifndef INCLUDED_SPSEMUNION_
#define INCLUDED_SPSEMUNION_

#include <memory>

#include "../semunion/semunion.h"

class spSemUnion: public std::shared_ptr<SemUnion>
{
    public:
        spSemUnion();

        template <typename Type>
        spSemUnion(Type const &obj);

    private:
};

inline spSemUnion::spSemUnion()
:
    std::shared_ptr<SemUnion>(new SemUnion())
{}

template <typename Type>
inline spSemUnion::spSemUnion(Type const &obj)
:
    std::shared_ptr<SemUnion>(new SemUnion(obj))
{}

#endif
