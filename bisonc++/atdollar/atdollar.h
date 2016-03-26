#ifndef INCLUDED_ATDOLLAR_
#define INCLUDED_ATDOLLAR_

#include <string>
#include <utility>
#include <limits>

class AtDollar
{
    friend std::ostream &operator<<(std::ostream &out, AtDollar const &atd);

    public:
        enum Pattern        // A: at, D represents $, ref: (), _: -nr, n: nr
        {                   //      m (= member): .  p (= pointer) -> t: <TAG>
            AA,             // @@
            An,             // @nr

            DD,             // $$
            Dn,             // $nr
            D_,             // $-nr

            refDD,          // ($$)
            refDn,          // ($nr)
            refD_,          // ($-nr)

            DDm,            // $$.
            Dnm,            // $nr.
            D_m,            // $-nr.

            DDp,            // $$->
            Dnp,            // $nr->
            D_p,            // $-nr->

            refDt_,         // ($<TAG>-nr)
            Dt_m,           // $<TAG>-nr.
            Dt_p            // $<TAG>-nr->
        };
            
//FBB
//        enum Type
//        {
//            AT,
//            DOLLAR,
//            DEREF
//        };

//        enum Action
//        {
//            RETURN_VALUE,
//            NUMBERED_ELEMENT,
//            TYPED_RETURN_VALUE,
//            TYPED_NUMBERED_ELEMENT
//        };

    private:
        size_t d_pos;
        size_t d_lineNr;
        std::string d_text;
        size_t d_length;
        Pattern d_pattern;
        std::string d_tag;
        std::string d_suffix;   // when callsMember() == true: . or -> 

                                // $$ or @@ if numeric_limits<int>::max()
        int d_nr = std::numeric_limits<int>::max(); 
        bool d_member = false;  // a member selector operator was used


//FBB        Type d_type;


    public:
        AtDollar() = default;       // only used by std::vector in Block


        AtDollar(size_t blockPos, size_t lineNr, std::string const &text);

//FBB                                                 // @@, $$, ($$), or $$.
//                                                    // @NR
//                                                    // $-?NR, $NR. ($NR)
//        AtDollar(Type type, size_t blockPos, size_t lineNr, 
//                 std::string const &text, int nr);
//
//
//                                                    // $<ID>-NR, ($<ID>-NR),
//                                                    // $<ID>-NR.   
//        AtDollar(Type type, size_t blockPos, size_t lineNr, 
//                 std::string const &text, std::string const &tag, int nr);

        Pattern pattern() const;

//FBB   Type type() const;              // AT (@@) or DOLLAR ($...) was used

        int nr() const;                 // nr used in $nr constructions
        std::string const &text() const;// the matched text
        std::string const &tag() const; // ID in $<ID>.. constructions
        size_t pos() const;             // offset inside the block
        size_t length() const;          // matched text length
        size_t lineNr() const;          // line nr in the grammar file
//FBB        Action action() const;          // %type associated or not
        bool callsMember() const;       // . was used -> .get required
        bool dollarDollar() const;      // true: $$ is being referred to
        std::string const &suffix() const;  // if callsMember():  "." or "->"

    private:
        void setAtPatterns();           // text[0] == '@'
        void setDollarPatterns();       // text[0] == '$'
        void setRefPatterns();          // text[0] == '('   // ) (emacs)
        void memberSelectorPatterns();  // text.back() == '.'
        void pointerPatterns();         // text.back() == '>'
        void setTagNr(size_t idx);      // idx beyond <

};

inline std::string const &AtDollar::suffix() const
{
    return d_suffix;
}
        
inline AtDollar::Pattern AtDollar::pattern() const
{
    return d_pattern;
}
        
//inline AtDollar::Type AtDollar::type() const
//{
//    return d_type;
//}
//FBB
        
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


