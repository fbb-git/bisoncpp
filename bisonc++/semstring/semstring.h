#ifndef INCLUDED_SEMSTRING_
#define INCLUDED_SEMSTRING_

#include <string>
#include "../sembase/sembase.h"

class SemString: public SemBase, public std::string
{
    public:
        SemString(std::string const &text);
};

inline SemString::SemString(std::string const &text)
:
    SemBase(Tag::STRING),
    std::string(text)
{}

template <>
struct Type<SemEnum::Tag::STRING>
{
    typedef SemString const &conversionType;
    typedef std::string const &semType;
};

#endif



