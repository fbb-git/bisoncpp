#include "generator.ih"

void Generator::threading(ostream &out) const
{
    key(out);

    if (Arg::instance().option(0, "thread-safe"))
        out << 
            "SR const *sr = s_state[d_state]; "
                            "   // get the appropriate state-table\n" <<

            setw(d_indent) << "" << 
            "int lastIdx = sr->d_lastIdx; "
                            "       // sentinel-index in the SR_ array\n"
            "\n" <<

            setw(d_indent) << "" << 
            "SR const *lastElementPtr = sr + lastIdx;\n" <<

            setw(d_indent) << "" << 
            "SR const *elementPtr = sr + 1; "
                            "     // start the search at s_xx[1]\n"
            "\n" <<

            setw(d_indent) << "" << 
            "while (elementPtr != lastElementPtr && "
                                        "elementPtr->d_token != d_token)\n" <<

            setw(d_indent) << "" << 
            "    ++elementPtr;\n";
    else
        out <<  
            "SR *sr = s_state[d_state];       "
                            "   // get the appropriate state-table\n" <<

            setw(d_indent) << "" << 
            "int lastIdx = sr->d_lastIdx; "
                            "       // sentinel-index in the SR_ array\n"
            "\n" <<

            setw(d_indent) << "" << 
            "SR *lastElementPtr = sr + lastIdx;\n" <<

            setw(d_indent) << "" << 
            "SR *elementPtr = sr + 1; "
                            "           // start the search at s_xx[1]\n"
            "\n" << 
            setw(d_indent) << "" << 
            "lastElementPtr->d_token = d_token;  // set search-token\n"
            "\n" <<

            setw(d_indent) << "" << 
            "while (elementPtr->d_token != d_token)\n" <<

            setw(d_indent) << "" << 
            "    ++elementPtr;\n";
}








