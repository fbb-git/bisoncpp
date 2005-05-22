#ifndef _INCLUDED_BLOCK_
#define _INCLUDED_BLOCK_

#include <vector>
#include <string>

class Block: public std::string
{
    unsigned d_line;
    
    public:
        typedef std::pair<unsigned, unsigned> Range;

    private:
        std::vector<Range>  d_skip;     // skip these ranges when processing
                                        // a block: it contains the begin and
                                        // end positions of strings and quotes 
                                        // found inside the matched block
    public:
        void clear();
        void operator+=(std::string const &text)
        {
            this->std::string::append(text);
        }
        void operator+=(Range const &range)
        {
            d_skip.push_back(range);
        }
        std::vector<Range>::const_reverse_iterator skipRbegin()
        {
            return d_skip.rbegin();
        }
        std::vector<Range>::const_reverse_iterator skipRend()
        {
            return d_skip.rend();
        }
        unsigned line() const
        {
            return d_line;
        }
        void setLine(unsigned line)
        {
            d_line = line;
        }
};

        
#endif

