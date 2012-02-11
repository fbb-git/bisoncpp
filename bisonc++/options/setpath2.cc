#include "options.ih"

//     1           2           3       4
// --target     %target     --dest   %dest       action: (D: default, W: warn
// ------------------------------------------------------
//     0           0           0       0           D
//     0           0           0       1           4
//     0           0           1       0           3       3 overrules 4
//     0           0           1       1           3
//     0           1           0       0           2 D     
//     0           1           0       1           4       specific overrules
//     0           1           1       0           3
//     0           1           1       1           3
//     1           0           0       0           1 D
//     1           0           0       1           4 W     W: --target ignored
//     1           0           1       0           3
//     1           0           1       1           3
//     1           1           0       0           1 D
//     1           1           0       1           4 W
//     1           1           1       0           3
//     1           1           1       1           3
// -------------------------------------------------------
// 
//     1           2           3       4
// --target     %target     --dest   %dest       action: (D: default, W: warn
// ------------------------------------------------------
//     0           0           1       0           3       3 overrules 4
//     0           0           1       1           3
//     0           1           1       0           3
//     0           1           1       1           3
//     1           0           1       0           3
//     1           0           1       1           3
//     1           1           1       0           3
//     1           1           1       1           3
// 
//     0           0           0       1           4      specific overrules
//     0           1           0       1           4                   target
//     1           0           0       1           4 W     W: --target ignored
//     1           1           0       1           4 W
// 
//     1           0           0       0           1 D    option overrules dir
//     1           1           0       0           1 D
//     0           1           0       0           2 D     
//     0           0           0       0           D
// -------------------------------------------------------


void Options::setPath(string *dest, int optChar, bool targetDirOption, 
                      char const *optionName, string const &className, 
                      char const *suffix)
{
    if (not Arg::instance().option(dest, optChar))  // catches '3'
    {
        if (not dest->empty())                      // catches '4'
        {
            if (targetDirOption)                    // '4 W' actions
                wmsg << "--target-directory ignored for %" << optionName << 
                        endl;
        }
        else                                        // Defaults:
            *dest = d_targetDirectory + className + suffix;
    }
}
        


