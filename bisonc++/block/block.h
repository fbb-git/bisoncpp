#ifndef _INCLUDED_BLOCK_
#define _INCLUDED_BLOCK_

#include <ostream>
#include <vector>
#include <string>

#include "../atdollar/atdollar.h"

class Block: private std::string
{
    friend std::ostream &operator<<(std::ostream &out, Block const &blk);

    size_t  d_line;
    std::string d_source;               // the source in which the block 
                                        // was found. The block's text itself
                                        // is in the Block's base class

    int     d_count = 0;                // curly braces nesting count, handled 
                                        // by clear(), close(), and open()

    std::vector<AtDollar> d_atDollar;   // @- and $-specifications

    bool d_usedDollarDollar = false;

    public:
        using std::string::empty;
        using std::string::find;
        using std::string::find_first_not_of;
        using std::string::find_first_of;
        using std::string::find_last_of;
        using std::string::insert;
        using std::string::length;
        using std::string::operator[];
        using std::string::replace;
        using std::string::substr;

        void clear();
                                       // clears the previous block contents
        void open(size_t lineno, std::string const &source);
        bool close();
                                                    // @@, $$, ($$), or $$.
        void dollar(size_t lineNr, std::string const &matched); 

                                                    // @NR
        void atIndex(size_t lineNr, std::string const &matched);

                                                    // $-?NR, $NR. ($NR)
        void dollarIndex(size_t lineNr, std::string const &matched);
                                        
//FBB OBSOLETE
//        void IDdollar(size_t lineNr, std::string const &matched);   // $<ID>$

                                                    // $<ID>-NR, ($<ID>-NR),
                                                    // $<ID>-NR.   
        void IDindex(size_t lineNr, std::string const &matched);    

        void operator+=(std::string const &text);
  
        operator bool() const;          // return true if a block is active

                                        // add text if a block is active,
        bool operator()(std::string  const &text);  // returns true if active

        std::vector<AtDollar>::const_reverse_iterator rbeginAtDollar() const;
        std::vector<AtDollar>::const_reverse_iterator rendAtDollar() const;

        size_t line() const;
        std::string const &source() const;  // the block's source file
        std::string const &str() const;     // the block's contents

        bool usedDollarDollar() const;      // used $$, $$., or $<ID>$
};

inline bool Block::usedDollarDollar() const
{
    return d_usedDollarDollar;
}

inline void Block::operator+=(std::string const &text)
{
    append(text);
}

inline Block::operator bool() const
{
    return d_count;
}

inline std::vector<AtDollar>::const_reverse_iterator 
Block::rbeginAtDollar() const
{
    return d_atDollar.rbegin();
}

inline std::vector<AtDollar>::const_reverse_iterator 
Block::rendAtDollar() const
{
    return d_atDollar.rend();
}

inline size_t Block::line() const
{
    return d_line;
}

inline std::string const &Block::source() const
{
    return d_source;
}

inline std::string const &Block::str() const
{
    return *this;
}

#endif

