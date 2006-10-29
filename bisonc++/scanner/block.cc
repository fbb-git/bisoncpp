#include "scanner.ih"

    // Process a block, and return true if a block was read.
    // the block holds the block-text and the skip-indices
bool Scanner::block(Block *block) 
{
    block->setLine(yylineno);

    int token = lex();

    if (token != '{')      
        return false;

    block->clear();

    size_t begin = 0;
    int count = 0;

    while (true)
    {
        *block += d_text;

        switch (token)
        {
            case '{':
                ++count;
            break;

            case '}':
                --count;
                if (count == 0)
                    return true;
            break;

            case STRING:
            case QUOTE:
                *block += Block::Range(begin, begin + d_text.length());
            break;

            case ENDFILE:
            unexpectedEOF();
        }

        d_retWS = true;
        token = lex();
        d_retWS = false;

        begin = block->length();
    }
}

