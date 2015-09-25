#include "options.ih"

//     1           2           3       4
// --target     %target     --dest   %dest       action: (D: default)
// ------------------------------------------------------
//     0           0           1       0           2    t+d (t may be empty)
//     0           0           1       1           2
//     0           1           1       0           2
//     0           1           1       1           2
//     1           0           1       0           2
//     1           0           1       1           2
//     1           1           1       0           2
//     1           1           1       1           2
//                                                 2
//     0           0           0       1           2
//     0           1           0       1           2
//     1           0           0       1           2 
//     1           1           0       1           2 
// 
//     1           0           0       0           1   t+D  (t may be empty)
//     1           1           0       0           1 
//     0           1           0       0           1
//     0           0           0       0           1
// -------------------------------------------------------


void Options::setPath(string *dest, 
                      int optChar, 
                      string const &defaultFilename, 
                      char const *defaultSuffix,
                      char const *optionName)
{
    if 
    (
        d_arg.option(dest, optChar)             // try to get the option
        &&
        dest->find('/') != string::npos
    )
        emsg << "`--" << optionName << "' option: no path names" << endl;

    if (dest->empty())                  // no value in dest then use a default
        *dest = defaultFilename + defaultSuffix;  // filename and suffix

//    d_warnOptions.insert(optionName);

    *dest = d_targetDirectory + *dest; // prefix the target (may be empty)
}
        


