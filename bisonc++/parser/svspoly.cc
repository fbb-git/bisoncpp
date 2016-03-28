#include "parser.ih"

    // $nr _$nr $-nr _$-nr
bool Parser::svsPoly(int nElements, Block &block,AtDollar const &atd)
{
    return svsPolyReplace(nElements, block, atd, "");
}
