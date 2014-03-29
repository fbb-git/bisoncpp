#include "generator.ih"

Generator::Map Generator::s_insert =
{
    {"actioncases",                 &Generator::actionCases},
    {"lex",                         &Generator::lex},
    {"scanner.h",                   &Generator::scannerH},
    {"scannerobject",               &Generator::scannerObject},
    {"baseclass",                   &Generator::baseClass},
    {"class.h",                     &Generator::classH},
    {"class.ih",                    &Generator::classIH},
    {"debug",                       &Generator::debug},
    {"debugdecl",                   &Generator::debugDecl},
    {"debuginit",                   &Generator::debugInit},
    {"debugfunctions",              &Generator::debugFunctions},
    {"debugincludes",               &Generator::debugIncludes},
    {"debuglookup",                 &Generator::debugLookup},
    {"errorverbose",                &Generator::errorVerbose},
    {"namespace-open",              &Generator::namespaceOpen},
    {"namespace-close",             &Generator::namespaceClose},
    {"namespace-use",               &Generator::namespaceUse},
    {"polymorphic",                 &Generator::polymorphic},
    {"polymorphicInline",           &Generator::polymorphicInline},
    {"polymorphicSpecializations",  &Generator::polymorphicSpecializations},
    {"preincludes",                 &Generator::preIncludes},
    {"print",                       &Generator::print},
    {"requiredtokens",              &Generator::requiredTokens},
    {"staticdata",                  &Generator::staticData},
    {"threading",                   &Generator::threading},
    {"tokens",                      &Generator::tokens},
    {"LTYPE",                       &Generator::ltype},
    {"LTYPEdata",                   &Generator::ltypeData},
    {"LTYPEpop",                    &Generator::ltypePop},
    {"LTYPEpush",                   &Generator::ltypePush},
    {"LTYPEresize",                 &Generator::ltypeResize},
    {"LTYPEstack",                  &Generator::ltypeStack},
    {"STYPE",                       &Generator::stype},
};

Generator::BMap Generator::s_atBol =
{
    {"@insert-stype",               &Generator::ifInsertStype},
    {"@printtokens",                &Generator::ifPrintTokens},
    {"@ltype",                      &Generator::ifLtype},
    {"@lthread-safe",               &Generator::ifThreadSafe},

//    {"@else",                       &Generator::ifElse},
};

char const *Generator::s_atFlag = "\\@";

vector<Generator::At> Generator::s_at =
{
    At("\\@tokenfunction",          &Generator::atTokenFunction),
    At("\\@matchedtextfunction",    &Generator::atMatchedTextFunction),
    At("\\@ltype",                  &Generator::atLtype),
    At("\\@$",                      &Generator::atNameSpacedClassname),
    At("\\@",                       &Generator::atClassname),
};
  
//size_t const Generator::s_baseFlagSize = 2; // backslash and @
//
//char const *Generator::s_namespaceBaseFlag = "\\@$";
//size_t const Generator::s_namespaceBaseFlagSize = 3; // backslash, $ and @
//FBB





