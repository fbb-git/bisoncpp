#ifndef _INCLUDED_OM_
#define _INCLUDED_OM_

#include <iosfwd>

class OM
{
    public:
        enum InsType
        {
            RAW,
            STD,
            EXTENDED,
            SPECIAL,
            SR,
            SYMTYPE,
        };

    private:
        static InsType s_type;
        static InsType s_saved;

        static std::ostream &(*s_manipulator[])(std::ostream &out);

    public:
        static std::ostream &raw(std::ostream &out);   // manipulators
        static std::ostream &std(std::ostream &out);   
        static std::ostream &ext(std::ostream &out);   
        static std::ostream &spec(std::ostream &out);   
        static std::ostream &sr(std::ostream &out);   
        static std::ostream &symtype(std::ostream &out);   
        static std::ostream &reset(std::ostream &out);   

        static void setType(InsType type);
        static InsType type();
};

inline void OM::setType(InsType type)
{
    s_saved = s_type = type;
}

inline OM::InsType OM::type()
{
    return s_type;
}

inline std::ostream &OM::raw(std::ostream &out) 
{
    s_type = RAW;
    return out;
}

inline std::ostream &OM::std(std::ostream &out)
{
    s_type = STD;
    return out;
}


inline std::ostream &OM::sr(std::ostream &out)
{
    s_type = SR;
    return out;
}

inline std::ostream &OM::symtype(std::ostream &out)
{
    s_type = SYMTYPE;
    return out;
}

#include <iostream>

inline std::ostream &OM::ext(std::ostream &out)
{
    s_type = EXTENDED;
std::cerr << "Set s_type to " << s_type << "\n";
    return out;
}

inline std::ostream &OM::spec(std::ostream &out)
{
    s_type = SPECIAL;
    return out;
}

inline std::ostream &OM::reset(std::ostream &out)
{
    s_type = s_saved;
    return out;
}
        
#endif




