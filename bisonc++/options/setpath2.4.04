#include "options.ih"

// options overrule directives
// path specifications overrule target specifications
// paths in directives and a targetdir option results in a warning

// -t: --target-directory options was specified
// %t: %target-directory directive was specified
// -d: --destination option was specified
// -dp: --destination option using a path (/) was specified
// %d: %destination directive was specified
// %dp: %destination directive using a path (/) was specified

//  D:  default destination value
//  d:  destination directive value
//  o:  destination option value
//  t:  target-directory value
//  -:  combination cannot occur (e.g., both -d and -dp)
//  W:  provide warning about ignored t


// No destination option:
// 
//     no target spec:
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   0           0   0   D       1
//     0   0           0   1   d       2
//     0   0           1   0   d       2
//     0   0           1   1   -
// 
//     target spec:
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   1           0   0   t + D   1
//     0   1           0   1   d       2
//     0   1           1   0   t + d   2
//     0   1           1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   0           0   0   t + D   1
//     1   0           0   1   d   (W) 3
//     1   0           1   0   t + d   2
//     1   0           1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   1           0   0   t + D   1
//     1   1           0   1   d   (W) 3
//     1   1           1   0   t + d   2
//     1   1           1   1   -
// 
// Destination option was used:
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   0   0   1   0   0   o       5
//     0   0   0   1   0   1   o       5
//     0   0   0   1   1   0   o       5
//     0   0   0   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   0   1   0   0   0   o       5
//     0   0   1   0   0   1   o       5
//     0   0   1   0   1   0   o       5
//     0   0   1   0   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   0   1   1   0   0   -
//     0   0   1   1   0   1   -
//     0   0   1   1   1   0   -
//     0   0   1   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   1   0   1   0   0   o       5
//     0   1   0   1   0   1   o       5
//     0   1   0   1   1   0   o       5
//     0   1   0   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   1   1   0   0   0   o       5
//     0   1   1   0   0   1   o       5
//     0   1   1   0   1   0   o       5
//     0   1   1   0   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     0   1   1   1   0   0   -
//     0   1   1   1   0   1   -
//     0   1   1   1   1   0   -
//     0   1   1   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   0   0   1   0   0   o       5
//     1   0   0   1   0   1   o       5
//     1   0   0   1   1   0   o       5
//     1   0   0   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   0   1   0   0   0   t + o   4
//     1   0   1   0   0   1   t + o   4
//     1   0   1   0   1   0   t + o   4
//     1   0   1   0   1   1   - 
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   0   1   1   0   0   -
//     1   0   1   1   0   1   -
//     1   0   1   1   1   0   -
//     1   0   1   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   1   0   1   0   0   o       5
//     1   1   0   1   0   1   o       5
//     1   1   0   1   1   0   o       5
//     1   1   0   1   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   1   1   0   0   0   t + o   4
//     1   1   1   0   0   1   t + o   4
//     1   1   1   0   1   0   t + o   4
//     1   1   1   0   1   1   -
// 
//    -t  %t  -d -dp  %d %dp   use:    action:
//     1   1   1   1   0   0   -
//     1   1   1   1   0   1   -
//     1   1   1   1   1   0   -
//     1   1   1   1   1   1   -

void Options::setPath(string *dest, int optChar, bool targetDirOption, 
                      char const *optionName, string const &defaultFilename, 
                      char const *suffix)
{
    if (not d_arg.option(dest, optChar))        // no dest. option
    {
            // path specification used
        if (dest->find('/') != string::npos)
        {
            if (targetDirOption)     //  #3
                wmsg << "--target-directory ignored for %" << 
                        optionName << ' ' << *dest << endl;
        }
        else
            *dest = d_targetDirectory +         // may be empty
                (
                    dest->empty() ?             // no dest. specified
                        defaultFilename + suffix                    // #1
                    :
                        *dest                                       // #2
                );
    }
    else            // targetDirOption + dest. option w/o path provided:
    {
        if (targetDirOption && dest->find('/') == string::npos)
            *dest = d_targetDirectory + *dest;                      // # 4
    }
    // otherwise:                                                   // # 5
    
    cleanDir(*dest, false);
}
        



