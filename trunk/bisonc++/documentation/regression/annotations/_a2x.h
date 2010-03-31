#ifndef _INCLUDED_BOBCAT_A2X_
#define _INCLUDED_BOBCAT_A2X_

#include <sstream>
#include <string>

class A2x: public std::istringstream
{
    static bool s_lastFail;

    public:
        A2x();
        A2x(char const *txt);          // initialize from text
        A2x(std::string const &str);
        A2x(A2x const &other);

        template <typename Type>
        operator Type();

        template <typename Type>
        Type to();

        A2x &operator=(char const *txt);

        A2x &operator=(std::string const &str);
        A2x &operator=(A2x const &other);

        static bool lastFail();
};

inline A2x::A2x()
{}

inline A2x::A2x(char const *txt)                    // initialize from text
:
    std::istringstream(txt)
{}

inline A2x::A2x(std::string const &str)
:
    std::istringstream(str.c_str())
{}

inline A2x::A2x(A2x const &other)
:
    std::istringstream(other.str())
{}

template <typename Type>
inline Type A2x::to()
{
    Type t;

    return (s_lastFail = (*this >> t).fail()) ? Type() : t;
}

template <typename Type>
inline A2x::operator Type()
{
    return to<Type>();
}

inline A2x &A2x::operator=(std::string const &str)
{
    return operator=(str.c_str());
}            

inline A2x &A2x::operator=(A2x const &other)
{
    return operator=(other.str());
}

inline bool A2x::lastFail()
{
    return s_lastFail;
}

#endif
