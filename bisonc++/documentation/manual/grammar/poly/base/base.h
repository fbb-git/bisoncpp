#ifndef _INCLUDED_BASE_
#define _INCLUDED_BASE_

#include <iosfwd>

enum Tag
{
    INT,
    TEXT
};

template <Tag>
struct TagType
{};

class Base
{
    public:
        virtual ~Base();
        std::ostream &insert(std::ostream &os) const;

    private:
        virtual std::ostream &v_insert(std::ostream &os) const = 0;
};

inline Base::~Base()
{}

inline std::ostream &Base::insert(std::ostream &out) const
{
    return v_insert(out);
}

inline std::ostream &operator<<(std::ostream &out, Base const &obj)
{
    return obj.insert(out);
}

#endif
