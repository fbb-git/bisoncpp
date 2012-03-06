#ifndef _INCLUDED_SEMANTIC_
#define _INCLUDED_SEMANTIC_

#include <ostream>
#include <memory>

#include "../int/int.h"
#include "../text/text.h"

class Semantic: public std::shared_ptr<Base>
{
    public:
        template <typename>
        void assign(std::string const &matched);
};

template <>
inline void Semantic::assign<TagType<Tag::INT>>(std::string const &matched)
{
    reset(new Int(matched));
}

template <>
inline void Semantic::assign<TagType<Tag::TEXT>>(std::string const &matched)
{
    reset(new Text(matched));
}

inline std::ostream &operator<<(std::ostream &out, Semantic const &obj)
{
    return out << *obj;
}

#endif




