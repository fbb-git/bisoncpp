// Recompile this file if the skeleton locations in INSTALL.im change

#include "options.ih"
#include "SKEL"

size_t Options::s_defaultStackExpansion = 10;

char Options::s_defaultSkeletonDirectory[]      = _Skel_;
char Options::s_defaultClassName[]              = "Parser";
char Options::s_defaultParsefunSource[]         = "parse.cc";
char Options::s_defaultBaseClassSkeleton[]      = "bisonc++base.h";
char Options::s_defaultClassSkeleton[]          = "bisonc++.h";
char Options::s_defaultImplementationSkeleton[] = "bisonc++.ih";
char Options::s_defaultParsefunSkeleton[]       = "bisonc++.cc";
char Options::s_defaultPolymorphicSkeleton[]    = "bisonc++polymorphic";
char Options::s_defaultPolymorphicCodeSkeleton[]= "bisonc++polymorphic.code";

    // the defaults are flexc++-defaults.
    // use --flex or %flex or explicit options to use  flex defaults

char Options::s_defaultScannerClassName[]           = "Scanner";
char Options::s_defaultScannerMatchedTextFunction[] = "d_scanner.matched()";
char Options::s_YYText[]                        = "d_scanner.YYText()";

char Options::s_defaultScannerTokenFunction[]   = "d_scanner.lex()";
char Options::s_yylex[]                         = "d_scanner.yylex()";

Options *Options::s_options = 0;

unordered_map<string, Options::Value> Options::s_value 
{
    { "true",   Options::ON     },
    { "on",     Options::ON     },
    { "false",  Options::OFF    },
    { "off",    Options::OFF    },
    { "quiet",  Options::QUIET  },
    { "warn",   Options::WARN   },
    { "std",    Options::STD    }
};
