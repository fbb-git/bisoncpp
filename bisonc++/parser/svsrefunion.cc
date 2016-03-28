#include "parser.ih"

    // $nr _$nr $-nr _$-nr
bool Parser::svsRefUnion(int nElements, Block &block,AtDollar const &atd)
{
    return 
        (this->*
            (atd.refByScanner() ?
                &Parser::svsUnionReplace
            :
                &Parser::svsReplace
            )
        )(nElements, block, atd, "");
}
