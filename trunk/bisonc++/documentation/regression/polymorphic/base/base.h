#ifndef _INCLUDED_BASE_
#define _INCLUDED_BASE_

    // DON'T do this in real life:
using namespace std;

class Base
{
    public:
        virtual ~Base();
        virtual Base *clone() const = 0;
        virtual ostream &insert(ostream &os) const = 0;
};

inline Base::~Base()
{}
        
inline ostream &operator<<(ostream &out, Base const &obj)
{
    return obj.insert(out);
}

#endif
