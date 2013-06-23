#include "options.ih"

void Options::assign(std::string *target, PathType pathType, 
                                          char const *declTxt)
{
    if (target->empty())
    {
        d_warnOptions.insert(declTxt);
        *target = accept(pathType, declTxt);
    }
    else
        emsg << "%" << declTxt << " multiply specified" << endl;
}
        
