#include "scanner.ih"

void Scanner::pushSource()
{
    undelimit(true);                    // remove " " and < > delimiters

//    if (d_state.size() == d_maxDepth)
//        lineMsg(fmsg) << "Max. inclusion nesting (" << d_maxDepth << 
//                    ") reached" << endl;

    d_nextSource = String::unescape(d_matched);

//    recursiveInclusion();

    pushStream(d_nextSource);

    d_include = false;              // %include processed
}
