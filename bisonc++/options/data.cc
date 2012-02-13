// Recompile this file if the skeleton locations in INSTALL.im change

#include "options.ih"
#include "SKEL"

char Options::s_defaultSkeletonDirectory[]      = _Skel_;
char Options::s_defaultTargetDirectory[]        = "";
char Options::s_defaultClassName[]              = "Parser";
char Options::s_defaultParsefunSource[]         = "parse.cc";
char Options::s_defaultBaseClassSkeleton[]      = "bisonc++base.h";
char Options::s_defaultClassSkeleton[]          = "bisonc++.h";
char Options::s_defaultImplementationSkeleton[] = "bisonc++.ih";
char Options::s_defaultParsefunSkeleton[]       = "bisonc++.cc";
char Options::s_defaultScannerMatchedTextFunction[] = "d_scanner.matched()";
char Options::s_defaultScannerTokenFunction[]   = "d_scanner.lex()";

Options Options::s_options;
