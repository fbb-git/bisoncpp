#ifndef INCLUDED_SEMBASE_
#define INCLUDED_SEMBASE_

#include <iosfwd>
class Block;

class SemBase
{
    public:
        enum class Tag
        {
            STRING,
            BOOL,
            SIZE_T,
            BLOCK,
            TERMINAL,
            SYMBOL
        };

    private:
        Tag d_tag;

    public:
        virtual ~SemBase();
        Tag tag() const;

    protected:
        SemBase(Tag tag);
        SemBase(SemBase const &other) = default;
};

inline SemBase::Tag SemBase::tag() const
{
    return d_tag;
}

inline SemBase::SemBase(Tag tag)
:
    d_tag(tag)
{}
    
#endif


