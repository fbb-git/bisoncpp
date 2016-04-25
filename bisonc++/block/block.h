#ifndef _INCLUDED_BLOCK_
#define _INCLUDED_BLOCK_

#include <ostream>
#include <vector>
#include <string>

#include "../atdollar/atdollar.h"

class Block: private std::string
{
    friend std::ostream &operator<<(std::ostream &out, Block const &blk);

    size_t  d_lineNr;

    std::string d_source;               // the source in which the block 
                                        // was found. The block's text itself
                                        // is in the Block's base class

    int     d_count = 0;                // curly braces nesting count, handled 
                                        // by clear(), close(), and open()

    std::vector<AtDollar> d_atDollar;   // @- and $-specifications

    bool d_assignment = false;

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

        void atDollar(size_t lineNr, std::string const &text, 
                                bool assignment, bool refByScanner = false);
     
        void operator+=(std::string const &text);
  
        operator bool() const;          // return true if a block is active

                                        // add text if a block is active,
        bool operator()(std::string  const &text);  // returns true if active

        std::vector<AtDollar>::const_reverse_iterator rbeginAtDollar() const;
        std::vector<AtDollar>::const_reverse_iterator rendAtDollar() const;

        size_t lineNr() const;
        void   setLineNr(size_t lineNr);
        std::string const &source() const;  // the block's source file
        std::string const &str() const;     // the block's contents

        bool assignment() const;            // used '$$ ='
};

inline bool Block::assignment() const
{
    return d_assignment;
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

inline size_t Block::lineNr() const
{
    return d_lineNr;
}

inline void Block::setLineNr(size_t lineNr)
{
    d_lineNr = lineNr;
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

