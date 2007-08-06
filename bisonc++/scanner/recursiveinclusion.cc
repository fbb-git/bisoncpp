#include "scanner.ih"

void Scanner::recursiveInclusion()
{
    vector<FileInfo>::iterator
        it = find_if(d_fileInfo.begin(), d_fileInfo.end(), 
                FnWrap1c<FileInfo const &, string const &, bool>
                        (checkFilename, d_nextSource));

    if (it != d_fileInfo.end())
        lineMsg() << "Recursive inclusion of `" << d_nextSource << 
                                                            "'" << fatal;
}

