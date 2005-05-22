#ifndef _INCLUDED_ERRNO_H_
#define _INCLUDED_ERRNO_H_

#include <string>
#include <sstream>
#include <iosfwd>
#include <exception>
#include <iostream>

namespace FBB
{
    class Errno: public std::ostringstream, public std::exception
    {
        int d_errno;
        std::string d_msg;

        mutable std::string d_what;
        
        public:
            Errno();
            Errno(char const *prefix); 
            Errno(int errnr, char const *text);
            Errno(Errno const &other) throw();
            virtual ~Errno() throw()
            {}
            virtual const char *what() const throw();
            int which() const throw()
            {
                return d_errno;
            }

        private:
            void Errno::initMsg();
    };

    inline std::ostream &insertable(std::ostream &errnoObject)
    {
        return errnoObject;
    }

    inline Errno *throwable()
    {
        return 0;
    }

}

inline FBB::Errno &operator<<(std::ostream &str, FBB::Errno *(*)())
{
    return *static_cast<FBB::Errno *>(&(str << std::flush));
}
   

#endif
