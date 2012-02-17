#ifndef INCLUDED_SEMSIZET_
#define INCLUDED_SEMSIZET_

#include "../sembase/sembase.h"

class SemSizeT: public SemBase
{
    size_t d_size;

    public:
        SemSizeT(size_t size = 0);

    private:
        virtual SemBase *v_clone() const;
        virtual size_t v_size() const;
};

inline SemSizeT::SemSizeT(size_t size)
:
    d_size(size)
{}
        
#endif
