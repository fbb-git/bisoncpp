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

    int     d_count;                    // curly braces nesting count, handled 
                                        // by clear(), close(), and open()

    std::vector<AtDollar> d_atDollar;   // @- and $-specifications

    public:
        Block();

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

        void dollar(size_t lineNr, std::string const &matched,  // $$ or $$.
                    bool member); 

        void atIndex(size_t lineNr, std::string const &matched);     // @NR

                                                            // $-?NR or $-?NR.
        void dollarIndex(size_t lineNr, std::string const &matched, 
                         bool member);   
                                        
        void IDdollar(size_t lineNr, std::string const &matched);   // $<ID>$

                                                            // $<ID>-?NR   
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
};

inline Block::Block()
:
    d_count(0)
{}

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

