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

namespace FBB
{
    class Mstream;
}

class Scanner: private yyFlexLexer
{
    struct FileInfo
    {
        std::string d_name;
        size_t      d_lineno;
        std::ifstream    *d_in;
        
        FileInfo(std::string name, size_t lineno)
        :
            d_name(name),
            d_lineno(lineno),
            d_in(new std::ifstream(name.c_str()))
        {}
    };

    std::ifstream   d_in;           // stream currently read

    size_t          d_maxDepth;     // max. file inclusion depth

    size_t          d_number;       // only valid after tokens NUMBER and
                                    // after escape(), octal() and 
                                    // hexadecimal(). Illegal (long)
                                    // character constants (> 1 char) have bit
                                    // 8 set.

    bool            d_include;      // set to true/false by lexer-actions
    bool            d_includeOnly;

    char            d_commentChar[2];   // set to ' ' in `lexer' when C
                                    // comment without \n is matched,
                                    // otherwise set to \n. See
                                    // `lexer' for details

    std::string     d_nextSource;   // with the %include directive

    std::stack<yy_buffer_state *>   d_state;        // used when switching
    std::vector<FileInfo>           d_fileInfo;     // streams

    Block           d_block;            // action block retrieved fm the input

    std::string     d_canonicalQuote;   // canonical quoted ident.
    
    public:
        using yyFlexLexer::YYText;
        using yyFlexLexer::set_debug;
        using yyFlexLexer::lineno;

        Scanner(std::string const &fname);
        int yylex();
        Block &block();
        std::string const &canonicalQuote();
        void clearBlock();
        std::ostream &lineMsg(FBB::Mstream &mstream);
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
    return info.d_name == nextSource;
}

inline std::string const &Scanner::sourceName() const
{
    return d_fileInfo.back().d_name;
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



