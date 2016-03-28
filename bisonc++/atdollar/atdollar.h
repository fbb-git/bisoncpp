#ifndef INCLUDED_ATDOLLAR_
#define INCLUDED_ATDOLLAR_

#include <string>
#include <utility>
#include <limits>

class AtDollar
{
    friend std::ostream &operator<<(std::ostream &out, AtDollar const &atd);

    public:

        // Pattern is determined by the constructor
        enum Pattern        // A: at, D represents $, ref: (), _: -nr, n: nr
        {                   //      m (= member): .  p (= pointer) -> t: <TAG>
            AA,             // @@
            An,             // @nr

            DD,             // $$
            refDD,          // _$$
            DDm,            // $$.
            DDp,            // $$->

            Dn,             // $nr
            refDn,          // _$nr
            Dnm,            // $nr.
            Dnp,            // $nr->

            D_,             // $-nr
            refD_,          // _$-nr
            D_m,            // $-nr.
            D_p,            // $-nr->

            Dt_,            // $<TAG>-nr
            Dt_m,           // $<TAG>-nr.
            Dt_p,           // $<TAG>-nr->
        };
            
    private:
        size_t d_pos;
        size_t d_lineNr;
        std::string d_text;
        size_t d_length;
        Pattern d_pattern;
        std::string d_tag;

                                // $$ or @@ if numeric_limits<int>::max()
        int d_nr = std::numeric_limits<int>::max(); 

    public:
        AtDollar() = default;       // only used by std::vector in Block


        AtDollar(size_t blockPos, size_t lineNr, std::string const &text);

        Pattern pattern() const;

        int nr() const;                 // nr used in $nr constructions
        std::string const &text() const;// the matched text
        std::string const &tag() const; // ID in $<ID>.. constructions
        size_t pos() const;             // offset inside the block
        size_t length() const;          // matched text length
        size_t lineNr() const;          // line nr in the grammar file
        bool dollarDollar() const;      // true: $$ is being referred to

        bool stackElement() const;

    private:
//FBB        void memberSelectorPatterns();  // text.back() == '.'
//FBB        void pointerPatterns();         // text.back() == '>'
        void setTagNr(size_t idx);      // idx beyond <

        void setAtPatterns();           // text[0] == '@'
        void setRefPatterns();          // text[0] == '_'
        void setDollarPatterns();       // text[0] == '$'
        void setDollarDollarPatterns();
        void setTagPatterns();
        void setNumberPatterns();
};

inline AtDollar::Pattern AtDollar::pattern() const
{
    return d_pattern;
}
        
inline int AtDollar::nr() const
{
    return d_nr;
}
        
inline bool AtDollar::dollarDollar() const
{
    return d_pattern == DD;
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


