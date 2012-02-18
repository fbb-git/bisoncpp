#ifndef INCLUDED_SEMBASE_
#define INCLUDED_SEMBASE_

#include <iosfwd>
class Block;

struct SemEnum
{
    enum class Tag
    {
        STRING,
        BOOL,
        SIZE_T,
        BLOCK,
        TERMINAL,
        SYMBOL
    };
};

template <SemEnum::Tag tag>
struct Type;

class SemBase: public SemEnum
{
    Tag d_tag;

    public:
        virtual ~SemBase();
        Tag tag() const;

        template <SemEnum::Tag tg_>
        typename Type<tg_>::semType as() const;

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

template <SemEnum::Tag tg_>
inline typename Type<tg_>::semType SemBase::as() const
{
    return dynamic_cast<typename Type<tg_>::conversionType>(*this);
}

#endif




