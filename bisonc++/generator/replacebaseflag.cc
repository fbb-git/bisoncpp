#include "generator.ih"

void Generator::replaceBaseFlag(string &line) const
{
//    string const &className = d_options.className();

    size_t pos = line.length();

    while ((pos = line.rfind(s_atFlag, pos) != string::npos)    // found \@
    {
        if (find(line, pos, at) != at.end())
            line.replace(pos, at.size, (this->*at.function)());
    }

//        if (line.find(s_namespaceBaseFlag) == pos)
//            line.replace(pos, s_namespaceBaseFlagSize, 
//                         d_options.nameSpace() + className);
//        else 
//            line.replace(pos, s_baseFlagSize, className);
//FBB
    }
}
