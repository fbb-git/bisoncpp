#ifndef _INCLUDED_FOLLOWSET_
#define _INCLUDED_FOLLOWSET_

#include <set>

#include "../firstset/firstset.h"
#include "../terminal/terminal.h"

class FollowSet
{
    friend std::ostream &operator<<(std::ostream &out, FollowSet const &fSet);

    bool d_EOF;             // true if {Follow} contains EOF
    std::set<Terminal const *> d_set;

    public:
        FollowSet();
        size_t setSize() const;
        void setEOF();
        bool hasEOF() const;
        FollowSet &operator+=(FollowSet const &other);
        FollowSet &operator+=(FirstSet const &firstSet);

    private:
        std::ostream &oInsert(std::ostream &out) const;
};

inline FollowSet::FollowSet()
:
    d_EOF(false)
{}

inline size_t FollowSet::setSize() const
{
    return d_set.size() + d_EOF;
}

inline void FollowSet::setEOF()
{
    d_EOF = true;
}

inline bool FollowSet::hasEOF() const
{
    return d_EOF;
}

inline std::ostream &operator<<(std::ostream &out, FollowSet const &followSet)
{
    return followSet.oInsert(out);
}


        
#endif
