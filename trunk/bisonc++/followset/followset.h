#ifndef _INCLUDED_FOLLOWSET_
#define _INCLUDED_FOLLOWSET_

#include <set>

#include "../firstset/firstset.h"
#include "../terminal/terminal.h"

class FollowSet: public std::set<Terminal const *>
{
    friend std::ostream &operator<<(std::ostream &out, FollowSet const &fSet);

    bool d_EOF;             // true if {Follow} contains EOF

    public:
        FollowSet()
        :
            d_EOF(false)
        {}
        size_t setSize() const
        {
            return size() + d_EOF;
        }
        void setEOF()
        {
            d_EOF = true;
        }
        bool hasEOF() const
        {
            return d_EOF;
        }
        FollowSet &operator+=(FollowSet const &other);
        FollowSet &operator+=(FirstSet const &firstSet);

    private:
        std::ostream &oInsert(std::ostream &out) const;
};

inline std::ostream &operator<<(std::ostream &out, FollowSet const &followSet)
{
    return followSet.oInsert(out);
}


        
#endif
