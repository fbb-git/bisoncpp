// Recompile this file if the skeleton locations in INSTALL.im change

#include "options.ih"
#include "SKEL"

char Options::s_defaultSkeletonDirectory[]       = _Skel_;
char Options::s_defaultLexFunctionName[]        = "lex";
char Options::s_defaultTargetDirectory[]        = "";
char Options::s_defaultClassName[]              = "Scanner";

Options Options::s_options;
