#include "parser.ih"

    // $nr _$nr $-nr _$-nr
bool Parser::svsUnion(int nElements, Block &block,AtDollar const &atd)
{
    return svsUnionReplace(nElements, block, atd, "");
}
