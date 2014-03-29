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

vector<Generator::At<bool>> Generator::s_atBol =
{
    At<bool>("@insert-stype",   &Generator::ifInsertStypeOpt),
    At<bool>("@printtokens",    &Generator::ifPrintTokens),
    At<bool>("@ltype",          &Generator::ifLtype),
    At<bool>("@lthread-safe",   &Generator::ifThreadSafe),
    At<bool>("@else",           &Generator::atElse),
    At<bool>("@",               &Generator::at),
};

char const *Generator::s_atFlag = "\\@";

vector<Generator::At<void>> Generator::s_at =
{
    At<void>("\\@tokenfunction",        &Generator::atTokenFunction),
    At<void>("\\@matchedtextfunction",  &Generator::atMatchedTextFunction),
    At<void>("\\@ltype",                &Generator::atLtype),
    At<void>("\\@$",                    &Generator::atNameSpacedClassname),
    At<void>("\\@",                     &Generator::atClassname),
};
  
//size_t const Generator::s_baseFlagSize = 2; // backslash and @
//
//char const *Generator::s_namespaceBaseFlag = "\\@$";
//size_t const Generator::s_namespaceBaseFlagSize = 3; // backslash, $ and @
//FBB





