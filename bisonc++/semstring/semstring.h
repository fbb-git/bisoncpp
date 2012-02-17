#ifndef INCLUDED_SEMSTRING_
#define INCLUDED_SEMSTRING_

#include <string>
#include "../sembase/sembase.h"

class SemString: private std::string, public SemBase
{
    public:
        SemString() = default;
        SemString(std::string const &text);

    private:
        virtual SemBase *v_clone() const;
        virtual std::string const &v_str() const;
};
   
inline SemString::SemString(std::string const &text)
:
    std::string(text)
{}
     
#endif
