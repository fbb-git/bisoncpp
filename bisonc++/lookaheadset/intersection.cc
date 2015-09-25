#include "lookaheadset.ih"

LookaheadSet LookaheadSet::intersection(LookaheadSet const &other) const
{
    Element const *setResult[max(size(), other.size())];

    LookaheadSet ret(
                    setResult, 
                    set_intersection
                    (
                        begin(), end(), 
                        other.begin(), other.end(),
                        setResult
                    )
                );

    ret.d_EOF = hasEOF() && other.hasEOF() ? e_withEOF : e_withoutEOF;

    return ret;
}
