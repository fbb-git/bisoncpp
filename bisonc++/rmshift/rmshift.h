#ifndef INCLUDED_RMSHIFT_
#define INCLUDED_RMSHIFT_

#include <vector>
#include <cstddef>

class RmShift
{
    public:
        typedef std::vector<RmShift>    Vector;
        typedef Vector::const_iterator  ConstIter;

    private:
        size_t d_idx;               // idx of the Next vector to remove.
        bool   d_forced;            // forced if not based on precedence or
                                    // associativity 
    public:
        RmShift() = default;        // only needed for vectors
        RmShift(size_t idx, bool forced);

        size_t idx() const;
        bool forced() const;       
};
        
inline size_t RmShift::idx() const
{
    return d_idx;
}

inline bool RmShift::forced() const
{
    return d_forced;
}

#endif
