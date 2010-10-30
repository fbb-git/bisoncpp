#include "scanner.ih"

void Scanner::pushSource(yy_buffer_state *current, size_t size)
{
    undelimit(true);                    // remove " " and < > delimiters

    if (d_state.size() == d_maxDepth)
        lineMsg(fmsg) << "Max. inclusion nesting (" << d_maxDepth << 
                    ") reached" << endl;

    d_nextSource = String::unescape(yytext);

    recursiveInclusion();
    d_fileInfo.push_back(FileInfo(d_nextSource, yylineno));
    ifstream *newStream = d_fileInfo.back().d_in;

    if (!*newStream)
        lineMsg(fmsg) << "Can't read `" << d_nextSource << "'" << endl;

    d_state.push(current);

    yylineno = 1;                   // start counting lines at 1
    yy_switch_to_buffer(yy_create_buffer(newStream, size));

    d_include = false;              // %include processed
}
