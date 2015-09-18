#include "generator.hh"

void Generator::replaceBaseFlag(string &line) const
{
//    string const &className = d_options.className();

    size_t pos = line.length();

    while ((pos = line.rfind(s_atFlag, pos)) != string::npos)   // found \@
    {
        auto iter = find(line, pos, s_at);

        if (iter != s_at.end())
            line.replace(pos, iter->size, (this->*iter->function)());
    }

//        if (line.find(s_namespaceBaseFlag) == pos)
//            line.replace(pos, s_namespaceBaseFlagSize, 
//                         d_options.nameSpace() + className);
//        else 
//            line.replace(pos, s_baseFlagSize, className);
//FBB
//    }
}
