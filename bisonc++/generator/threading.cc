#include "generator.ih"

void Generator::threading(ostream &out) const
{
    key(out);

    if (d_arg.option(0, "thread-safe"))
        out << 
            "SR__ const *sr = s_state[d_state__]; "
                            " // get the appropriate state-table\n" <<

            setw(d_indent) << "" << 
            "int lastIdx = sr->d_lastIdx; "
                            "       // sentinel-index in the SR_ array\n"
            "\n" <<

            setw(d_indent) << "" << 
            "SR__ const *lastElementPtr = sr + lastIdx;\n" <<

            setw(d_indent) << "" << 
            "SR__ const *elementPtr = sr + 1; "
                            "     // start the search at s_xx[1]\n"
            "\n" <<

            setw(d_indent) << "" << 
            "while (elementPtr != lastElementPtr && "
                                    "elementPtr->d_token != d_token__)\n" <<

            setw(d_indent) << "" << 
            "    ++elementPtr;\n";
    else
        out <<  
            "SR__ *sr = s_state[d_state__];     "
                            "   // get the appropriate state-table\n" <<

            setw(d_indent) << "" << 
            "int lastIdx = sr->d_lastIdx; "
                            "       // sentinel-index in the SR__ array\n"
            "\n" <<

            setw(d_indent) << "" << 
            "SR__ *lastElementPtr = sr + lastIdx;\n" <<

            setw(d_indent) << "" << 
            "SR__ *elementPtr = sr + 1; "
                            "           // start the search at s_xx[1]\n"
            "\n" << 
            setw(d_indent) << "" << 
            "lastElementPtr->d_token = d_token__;// set search-token\n"
            "\n" <<

            setw(d_indent) << "" << 
            "while (elementPtr->d_token != d_token__)\n" <<

            setw(d_indent) << "" << 
            "    ++elementPtr;\n";
}








