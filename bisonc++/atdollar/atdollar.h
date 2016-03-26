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
            DEREF
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
        std::string d_tag;
        std::string d_suffix;   // with 'callsMember(): . or -> 

        int d_nr;               // $$ if numeric_limits<int>::max()
        bool d_member = false;  // the member selector was used -> .get

    public:
        AtDollar() = default;       // only used by std::vector in Block


                                                    // @@, $$, ($$), or $$.
                                                    // @NR
                                                    // $-?NR, $NR. ($NR)
        AtDollar(Type type, size_t blockPos, size_t lineNr, 
                 std::string const &text, int nr);

                                                    // $<ID>-NR, ($<ID>-NR),
                                                    // $<ID>-NR.   
        AtDollar(Type type, size_t blockPos, size_t lineNr, 
                 std::string const &text, std::string const &tag, int nr);

        Type type() const;              // AT (@@) or DOLLAR ($...) was used
        int nr() const;                 // nr used in $nr constructions
        std::string const &text() const;// the matched text
        std::string const &tag() const; // ID in $<ID>.. constructions
        size_t pos() const;             // offset inside the block
        size_t length() const;          // matched text length
        size_t lineNr() const;          // line nr in the grammar file
        Action action() const;          // %type associated or not
        bool callsMember() const;       // . was used -> .get required
        bool dollarDollar() const;      // true: $$ is being referred to
        std::string const &suffix() const;  // if callsMember():  "." or "->"

    private:
        void suffixAndMember();
};

inline std::string const &AtDollar::suffix() const
{
    return d_suffix;
}
        
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
        
inline bool AtDollar::dollarDollar() const
{
    return d_nr == std::numeric_limits<int>::max() &&
            d_type == DOLLAR && not d_member;
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
        
inline std::string const &AtDollar::tag() const
{
    return d_tag;
}
        
#endif


