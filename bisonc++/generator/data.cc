#include "generator.ih"

Generator::Map Generator::s_insert =
{
    {"executeactioncases",          &Generator::executeActionCases},
    {"lex",                         &Generator::lex},
    {"scanner.h",                   &Generator::scannerH},
    {"scannerobject",               &Generator::scannerObject},
    {"baseclass",                   &Generator::baseClass},
    {"class.h",                     &Generator::classH},
    {"class.ih",                    &Generator::classIH},
    {"debug",                       &Generator::debug},
    {"debugdecl",                   &Generator::debugDecl},
    {"debugfunctions",              &Generator::debugFunctions},
    {"debugincludes",               &Generator::debugIncludes},
    {"debuglookup",                 &Generator::debugLookup},
    {"errorverbose",                &Generator::errorVerbose},
    {"idoftag",                     &Generator::idOfTag},
    {"namespace-open",              &Generator::namespaceOpen},
    {"namespace-close",             &Generator::namespaceClose},
    {"namespace-use",               &Generator::namespaceUse},
    {"polyincludes",                &Generator::polyIncludes},
    {"polymorphic",                 &Generator::polymorphic},
    {"polymorphicCode",             &Generator::polymorphicCode},
    {"polymorphicSpecializations",  &Generator::polymorphicSpecializations},
    {"preincludes",                 &Generator::preIncludes},
    {"print",                       &Generator::print},
    {"prompt",                      &Generator::prompt},
    {"baseclasscode",               &Generator::baseClassCode},
    {"actioncases",                 &Generator::actionCases},
    {"staticdata",                  &Generator::staticData},
    {"tokens",                      &Generator::tokens},
    {"warnTagMismatches",           &Generator::warnTagMismatches},
    {"LTYPE",                       &Generator::ltype},
    {"LTYPEclear",                  &Generator::ltypeClear},
    {"LTYPEdata",                   &Generator::ltypeData},
    {"LTYPEpop",                    &Generator::ltypePop},
    {"LTYPEpush",                   &Generator::ltypePush},
    {"LTYPEresize",                 &Generator::ltypeResize},
    {"LTYPEstack",                  &Generator::ltypeStack},
    {"STYPE",                       &Generator::stype},
};

vector<Generator::AtBool> Generator::s_atBol =
{
    AtBool("@insert-stype", &Generator::ifInsertStype),
    AtBool("@printtokens",  &Generator::ifPrintTokens),
    AtBool("@ltype",        &Generator::ifLtype),
    AtBool("@else",         &Generator::atElse),
    AtBool("@end",          &Generator::atEnd),
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
