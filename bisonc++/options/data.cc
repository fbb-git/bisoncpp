// Recompile this file if the skeleton locations in INSTALL.im change

#include "options.ih"
#include "SKEL"

char Options::s_defaultSkeletonDirectory[]      = _Skel_;
char Options::s_defaultTargetDirectory[]        = "";
char Options::s_defaultClassName[]              = "Parser";
char Options::s_defaultParsefunSource[]         = "parse.cc";
char Options::s_defaultBaseClassSkeleton[]      = _Skel_ "/bisonc++base.h";
char Options::s_defaultClassSkeleton[]          = _Skel_ "/bisonc++.h";
char Options::s_defaultImplementationSkeleton[] = _Skel_ "/bisonc++.ih";
char Options::s_defaultParsefunSkeleton[]       = _Skel_ "/bisonc++.cc";

Options Options::s_options;
