#include "rrconflict.ih"

void RRConflict::compareReductions(size_t second)
{
    second = d_reducible[second];

    RRData rrData(
        d_firstLA->intersection(
            d_itemVector[second].lookaheadSet()
        )
    );

    if (rrData.empty())                 // no overlap
        return;

    StateItem const &firstItem = d_itemVector[d_firstIdx];
    StateItem const &secondItem = d_itemVector[second];

    switch 
    (
        Terminal::comparePrecedence(
            firstItem.precedence(), secondItem.precedence()
        )
    )
    {
        case Terminal::EQUAL:
            rrData.setIdx(
                firstItem.nr() < secondItem.nr() ? 
                    RRData::KEEP_FIRST 
                : 
                    RRData::KEEP_SECOND,
                d_firstIdx, second
            );

            s_nConflicts += rrData.size();
        break;

        case Terminal::SMALLER:             // first precedence < second prec.
            rrData.setIdx(d_firstIdx);
        break;

        case Terminal::LARGER:              // shift precedence > prod. prec.
            rrData.setIdx(second);
        break;
    }

    d_rmReduction.push_back(rrData);
}

