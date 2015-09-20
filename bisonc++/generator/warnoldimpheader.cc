#include "generator.hh"

void Generator::warnOldImpHeader(string const &newIH) const
{
    size_t pos = newIH.find_last_of("./");          // find dot or /

    string oldIH = 
        (pos != string::npos && newIH[pos] == '/' ? // no dot
            newIH                                   // use  old IH
        :
            newIH.substr(0, pos)                    // or cut the extension
        ) + ".ih";


    if (Stat(oldIH) and not Stat(newIH))
        wmsg << "Old style internal header file found: " << oldIH << "\n"
                "   New style internal header file is generated: " << newIH << 
                                                                        "\n"
                "   You may want to move " << oldIH << " to " << newIH << 
                                          ", and change C++ source files\n"
                "   to #include \"" << newIH << "\" instead of "
                                            "#include \"" << oldIH << "\".\n"
                "   Consider running `convert2hh'.\n"
                "   Refer to section PRECOMPILED HEADERS in the bisonc++(1) "
                                            "man-page\n" 
                "   for additional information." << 
                endl;
}



