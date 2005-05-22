#ifndef _INCLUDED_A2X_H_
#define _INCLUDED_A2X_H_

#include <sstream>
#include <string>

class A2x: public std::istringstream
{
    public:
        A2x()
        {}

        A2x(char const *txt)                    // initialize from text
        :
            std::istringstream(txt)
        {}

        A2x(std::string const &str)
        :
            std::istringstream(str.c_str())
        {}

        template <typename T>
        operator T()
        {
            T t;

            return (*this >> t) ? t : T();
        }

        A2x &operator=(char const *txt);

        A2x &operator=(std::string const &str)
        {
            return operator=(str.c_str());
        }            

        A2x &operator=(A2x const &other)
        {
            return operator=(other.str());
        }
};

#endif
