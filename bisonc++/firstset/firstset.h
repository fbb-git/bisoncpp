#ifndef _INCLUDED_FIRSTSET_
#define _INCLUDED_FIRSTSET_

#include <set>
#include <iosfwd>

#include "../element/element.h"

class FirstSet: private std::set<Element const *>
{
    friend std::ostream &operator<<(std::ostream &out, FirstSet const &fset);

    bool d_epsilon;             // true if epsilon (the empty set indicator) 
                                // is in {First}

    protected:
        typedef std::set<Element const *> ElementSet;
//FBB        typedef std::set<Element const *> Baseclass;
        FirstSet(Element const **begin, Element const **end);

    public:
        using ElementSet::find;
        using ElementSet::begin;
        using ElementSet::end;
        using ElementSet::size;

        FirstSet();
        FirstSet(Element const *terminal);

        FirstSet &operator+=(FirstSet const &other);
        FirstSet &operator+=(ElementSet const &terminalSet);

        bool empty() const;
        bool hasEpsilon() const;
        bool operator==(FirstSet const &other) const;

        size_t setSize() const;

        void addEpsilon();
        void rmEpsilon();

        std::set<Element const *> const &set() const;

    private:
        std::ostream &insert(std::ostream &out) const;
};

inline bool FirstSet::operator==(FirstSet const &other) const
{
    return d_epsilon == other.d_epsilon && 
            *static_cast<std::set<Element const *> const *>(this) == other;
}

inline std::set<Element const *> const &FirstSet::set() const
{
    return *this;
}

inline FirstSet::FirstSet(Element const **begin, Element const **end)
:
    ElementSet{ begin, end },
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
    return !d_epsilon && ElementSet::empty();
}

inline std::ostream &operator<<(std::ostream &out, FirstSet const &firstSet)
{
    return firstSet.insert(out);
}

#endif
