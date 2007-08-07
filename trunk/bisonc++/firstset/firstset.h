#ifndef _INCLUDED_FIRSTSET_
#define _INCLUDED_FIRSTSET_

#include <set>
#include <iosfwd>

#include "../element/element.h"

class FirstSet: public std::set<Element const *>
{
    friend std::ostream &operator<<(std::ostream &out, FirstSet const &fset);

    bool d_epsilon;             // true if epsilon in {First}

    protected:
        typedef std::set<Element const *> Baseclass;
        FirstSet(Element const **begin, Element const **end);

    public:
        FirstSet();
        FirstSet(Element const *terminal);

        FirstSet &operator+=(FirstSet const &other);
        FirstSet &operator+=(std::set<Element const *> const &terminalSet);

        bool empty() const;
        bool hasEpsilon() const;
        bool operator==(FirstSet const &other) const;

        size_t setSize() const;

        void addEpsilon();
        void rmEpsilon();
    
    private:
        std::ostream &insert(std::ostream &out) const;

};

inline FirstSet::FirstSet(Element const **begin, Element const **end)
:
    Baseclass(begin, end),
    d_epsilon(false)
{}

inline FirstSet::FirstSet()
:
    d_epsilon(false)
{}

inline size_t FirstSet::setSize() const
{
    return size() + d_epsilon;
}

inline void FirstSet::rmEpsilon()
{
    d_epsilon = false;
}

inline void FirstSet::addEpsilon()
{
    d_epsilon = true;
}

inline bool FirstSet::hasEpsilon() const
{
    return d_epsilon;
}

inline bool FirstSet::empty() const
{
    return !d_epsilon && Baseclass::empty();
}

inline std::ostream &operator<<(std::ostream &out, FirstSet const &firstSet)
{
    return firstSet.insert(out);
}

#endif
