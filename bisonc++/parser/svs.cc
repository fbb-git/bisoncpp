#include "parser.ih"

    // $nr _$nr $-nr _$-nr
bool Parser::svs(int nElements, Block &block,AtDollar const &atd)
{
    return svsReplace(nElements, block, atd, "");
}
