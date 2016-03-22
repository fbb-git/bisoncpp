#ifndef INCLUDED_ATDOLLAR_
#define INCLUDED_ATDOLLAR_

#include <string>
#include <utility>
#include <limits>

class AtDollar
{
    friend std::ostream &operator<<(std::ostream &out, AtDollar const &atd);

    public:
        enum Type
        {
            AT,
            DOLLAR,
            STYPE,
        };

        enum Action
        {
            RETURN_VALUE,
            NUMBERED_ELEMENT,
            TYPED_RETURN_VALUE,
            TYPED_NUMBERED_ELEMENT
        };

    private:
        Type d_type;
        size_t d_lineNr;
        size_t d_pos;
        size_t d_length;
        std::string d_text;
        std::string d_id;
        int d_nr;           // $$ if numeric_limits<int>::max()
        bool d_member;
        bool d_stype;

    public:
        AtDollar() = default;       // only used by std::vector in Block

                                    // 1    STYPE__<>, $$, $$., $NR, $NR., 
                                    //      @@ or @NR
        AtDollar(Type type, size_t blockPos, size_t lineNr, 
                 std::string const &text, int nr, bool member);

                                    // 3    $<ID>$ or $<ID>-?NR 
        AtDollar(Type type, size_t blockPos, size_t lineNr, 
                 std::string const &text, std::string const &id, int nr);

        Type type() const;
        int nr() const;
        std::string const &text() const;
        std::string const &id() const;
        size_t pos() const;
        size_t length() const;
        size_t lineNr() const;
        Action action() const;
        bool callsMember() const;
        bool returnValue() const;   // $$ is being referred to
        bool stype() const;         // id == STYPE__
};

inline AtDollar::Type AtDollar::type() const
{
    return d_type;
}
        
inline int AtDollar::nr() const
{
    return d_nr;
}
        
inline bool AtDollar::callsMember() const
{
    return d_member;
}
        
inline bool AtDollar::returnValue() const
{
    return d_nr == std::numeric_limits<int>::max();
}
        
inline bool AtDollar::stype() const
{
    return d_stype;
}
        
inline size_t AtDollar::pos() const
{
    return d_pos;
}
        
inline size_t AtDollar::length() const
{
    return d_length;
}
        
inline size_t AtDollar::lineNr() const
{
    return d_lineNr;
}
        
inline std::string const &AtDollar::text() const
{
    return d_text;
}
        
inline std::string const &AtDollar::id() const
{
    return d_id;
}
        
#endif


