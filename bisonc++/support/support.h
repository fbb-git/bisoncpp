#ifndef _INCLUDED_SUPPORT_H_
#define _INCLUDED_SUPPORT_H_

#include <bobcat/tablesupport>

class Support: public FBB::TableSupport
{
    public:
       void vline() const;
       void vline(size_t col) const;
};

#endif
