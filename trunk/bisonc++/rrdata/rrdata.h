#ifndef _INCLUDED_RRDATA_
#define _INCLUDED_RRDATA_

#include <vector>
#include "../lookaheadset/lookaheadset.h"

    // Data used when processing R/R conflicts. Used by, e.g., StateItem
class RRData
{
    public:
        typedef std::vector<RRData>     Vector;
        typedef Vector::const_iterator  ConstIter;

        enum Keep
        {
            KEEP_FIRST,
            KEEP_SECOND,
        };

    private:
        LookaheadSet d_laSet;   // set of LA symbols
        bool d_forced;          // true if one of the two rules is explicitly
                                // kept. 
        size_t d_idx;           // index of item with reduced LA set
        size_t d_kept;          // index of item with kept LA set

    public:
        RRData(LookaheadSet first);

        bool empty() const;
        size_t keepIdx() const;
        size_t reduceIdx() const;
        size_t size() const;
        LookaheadSet const &lookaheadSet() const;
        void setIdx(Keep keep, size_t first, size_t second);
        void setIdx(size_t reduce);     // non-forced

        static bool isForced(RRData const &rrData);
};

inline LookaheadSet const &RRData::lookaheadSet() const
{
    return d_laSet;
}

inline bool RRData::empty() const
{
    return d_laSet.empty();
}

inline size_t RRData::size() const
{
    return d_laSet.fullSize();
}

inline void RRData::setIdx(size_t reduce)
{
    d_idx = reduce;
}

inline size_t RRData::reduceIdx() const
{
    return d_idx;
}

inline size_t RRData::keepIdx() const
{
    return d_kept;
}

inline bool RRData::isForced(RRData const &rrData)
{
    return rrData.d_forced;
}

#endif
