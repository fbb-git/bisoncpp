#ifndef INCLUDED_SEMBOOL_
#define INCLUDED_SEMBOOL_

#include "../sembase/sembase.h"

class SemBool: public SemBase
{
    bool d_logic;

    public:
        SemBool(bool logic = false);
};

inline SemBool::SemBool(bool logic)
:
    SemBase(Tag::BOOL),
    d_logic(logic)
{}
        
#endif
