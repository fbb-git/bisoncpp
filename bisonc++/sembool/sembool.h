#ifndef INCLUDED_SEMBOOL_
#define INCLUDED_SEMBOOL_

#include "../sembase/sembase.h"

class SemBool: public SemBase
{
    bool d_logic;

    public:
        SemBool(bool logic = false);
        operator bool() const;
};

inline SemBool::SemBool(bool logic)
:
    SemBase(Tag::BOOL),
    d_logic(logic)
{}

inline SemBool::operator bool() const
{
    return d_logic;
}

template <>
struct Type<SemEnum::Tag::BOOL>
{
    typedef SemBool const &conversionType;
    typedef bool semType;
};

        
#endif
