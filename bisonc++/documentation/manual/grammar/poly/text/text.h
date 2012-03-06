#ifndef _INCLUDED_TEXT_
#define _INCLUDED_TEXT_

#include <string>
#include <ostream>

#include "../base/base.h"

class Text: public Base
{
    std::string d_text;

    public:
        Text(std::string const &text);
    private:
        virtual std::ostream &v_insert(std::ostream &os) const;
};

inline Text::Text(std::string const &text)
:
    d_text(text)
{}

inline std::ostream &Text::v_insert(std::ostream &out) const
{
    return out << d_text;
}

#endif
