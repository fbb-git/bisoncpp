#ifndef _INCLUDED_BLOCK_
#define _INCLUDED_BLOCK_

#include <iosfwd>
#include <vector>
#include <string>

class Block: private std::string
{
    size_t  d_line;
    std::string d_source;               // the source in which the block 
                                        // was found. The block's text itself
                                        // is in the Block's base class

    int     d_count;                    // curly braces nesting count, handled 
                                        // by clear(), close(), and open()

    
    public:
        typedef std::pair<size_t, size_t> Range;

    private:
        std::vector<Range>  d_skip;     // skip these ranges when processing
                                        // a block: it contains the begin and
                                        // end positions of strings and quotes 
                                        // found inside the matched block
    public:
        Block();

        using std::string::empty;
        using std::string::find_first_of;
        using std::string::find_first_not_of;
        using std::string::find_last_of;
        using std::string::substr;
        using std::string::find;
        using std::string::length;

        using std::string::replace;
        using std::string::operator[];

        void clear();
                                        // clears the previous block contents
        void open(size_t lineno, std::string const &source);
        bool close();

        void saveDollar1(int offset);   // save $1 in $$ at the beginning
                                        // of a nested block

        void operator+=(std::string const &text);
  
        operator bool() const;          // return true if a block is active

                                        // add text if a block is active,
        bool operator()(std::string  const &text);  // returns true if active

        std::vector<Range>::const_reverse_iterator skipRbegin() const;
        std::vector<Range>::const_reverse_iterator skipRend() const;
        size_t line() const;
        std::string const &source() const;  // the block's source file
        std::string const &str() const;     // the block's contents

        void beginSkip();               // begins a new skip-area
        bool endSkip(std::string const &text); // if a block, text is added 
                                        // and the current skip-area is ended
        bool skip(std::string const &text); // if a block, text is added and
                                        // added to the skip-areas

};

inline Block::Block()
:
    d_count(0)
{}

inline void Block::operator+=(std::string const &text)
{
    append(text);
}

inline void Block::beginSkip()
{
    d_skip.push_back({length(), 0});
}

inline Block::operator bool() const
{
    return d_count;
}

inline std::vector<Block::Range>::const_reverse_iterator 
Block::skipRbegin() const
{
    return d_skip.rbegin();
}

inline std::vector<Block::Range>::const_reverse_iterator 
Block::skipRend() const
{
    return d_skip.rend();
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

