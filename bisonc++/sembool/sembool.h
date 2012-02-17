#ifndef INCLUDED_SEMBOOL_
#define INCLUDED_SEMBOOL_

#include "../sembase/sembase.h"

class SemBool: public SemBase
{
    bool d_logic;

    public:
        SemBool(bool logic = false);

    private:
        virtual SemBase *v_clone() const;
        virtual bool v_logic() const;
};

inline SemBool::SemBool(bool logic)
:
    d_logic(logic)
{}
        
#endif
