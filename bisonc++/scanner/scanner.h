#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <iosfwd>

#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <stack>

#if ! defined(_SKIP_YYFLEXLEXER_) && ! defined(_SYSINC_FLEXLEXER_H_)
#include <FlexLexer.h>
#define _SYSINC_FLEXLEXER_H_
#endif

#include "../block/block.h"

class Scanner: public yyFlexLexer
{
    typedef std::pair <std::string, size_t> FileInfo;

    std::ifstream   d_in;
    size_t          d_retWS;
    size_t          d_maxDepth;
    size_t          d_number;       // only valid after tokens NUMBER and
                                    // after escape(), octal() and 
                                    // hexadecimal(). Illegal (long)
                                    // character constants (> 1 char) have bit
                                    // 8 set.
    bool            d_include;
    bool            d_includeOnly;
    char            d_commentChar[2];   // set to ' ' in `lexer' when C
                                    // comment without \n is matched,
                                    // otherwise set to \n. See
                                    // `lexer' for details
    std::string     d_nextSource;   // with the %include directive

    std::stack<yy_buffer_state *>   d_state;
    std::vector<FileInfo>           d_fileInfo;

    Block           d_block;

    std::string     d_canonicalQuote;   // canonical quoted ident.
    
    public:
        Scanner(std::string const &fname);
        int yylex();
        Block &block();
        std::string const &canonicalQuote();
        void clearBlock();
        std::ostream &lineMsg();    // hides/modifies Msg's lineMsg()
        size_t number() const;
        std::string const &sourceName() const;  // gramfile currently processed
        bool hasBlock() const;
        bool includeOnly() const;
        void undelimit(bool warn);  // remove delimiters warn: about < >

    private:
        void checkZeroNumber();
        void recursiveInclusion();
        void pushSource(yy_buffer_state *current, size_t size);
        bool popSource(yy_buffer_state *current);

        void escape();
        void multiLineString();
        void octal();
        void hexadecimal();
        int setNumber();
        int yytextChk(int *nKept, int minLength, int ret);

        static bool checkFilename(FileInfo const &info, 
                                    std::string const &nextSource);
};

inline Block &Scanner::block()
{
    return d_block;
}

inline void Scanner::clearBlock()
{
    d_block.clear();
}

inline size_t Scanner::number() const
{
    return d_number;
}

inline bool Scanner::checkFilename(FileInfo const &info, 
                                    std::string const &nextSource)
{
    return info.first == nextSource;
}

inline std::string const &Scanner::sourceName() const
{
    return d_fileInfo.back().first;
}

inline bool Scanner::hasBlock() const
{
    return not d_block.empty();
}

inline bool Scanner::includeOnly() const
{
    return d_includeOnly;
}

#endif



