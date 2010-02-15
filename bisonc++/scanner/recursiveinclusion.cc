#include "scanner.ih"

void Scanner::recursiveInclusion()
{
    auto it = find_if(d_fileInfo.begin(), d_fileInfo.end(), 
                FnWrap::unary(checkFilename, d_nextSource));

    if (it != d_fileInfo.end())
        lineMsg() << "Recursive inclusion of `" << d_nextSource << 
                                                            "'" << fatal;
}

