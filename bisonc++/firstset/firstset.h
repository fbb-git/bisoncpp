#ifndef _INCLUDED_FIRSTSET_
#define _INCLUDED_FIRSTSET_

#include <set>
#include <iosfwd>

#include "../element/element.h"

class FirstSet: public std::set<Element const *>
{
    typedef std::set<Element const *> Baseclass;

    bool d_epsilon;             // true if epsilon in {First}

    public:
        FirstSet(Element const *terminal);
        FirstSet()
        :
            d_epsilon(false)
        {}

        unsigned setSize() const
        {
            return size() + d_epsilon;
        }
        void rmEpsilon()
        {
            d_epsilon = false;
        }
        void addEpsilon()
        {
            d_epsilon = true;
        }
        bool hasEpsilon() const
        {
            return d_epsilon;
        }
        FirstSet &operator+=(FirstSet const &other);
        FirstSet &operator+=(std::set<Element const *> const &terminalSet);

                                                // should be virtual.
        std::ostream &insert(std::ostream &out) const;

    private:
};

std::ostream &operator<<(std::ostream &out, FirstSet const &firstSet);

#endif
