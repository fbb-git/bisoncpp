#include "scanner.ih"

void Scanner::recursiveInclusion()
{
    auto it = find_if(
                d_fileInfo.begin(), d_fileInfo.end(), 
                [&](FileInfo const &info)
                {
                    return info.d_name == d_nextSource;
                }
            );

    if (it != d_fileInfo.end())
        lineMsg(fmsg) << "Recursive inclusion of `" << d_nextSource << '\'' << 
                                                                        endl;
}

