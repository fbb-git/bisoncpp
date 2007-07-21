#include "generator.ih"

Generator::MapValue Generator::s_mapValues[] =
{
    MapValue("actioncases",       &Generator::actionCases),
    MapValue("lex",               &Generator::lex),
    MapValue("scanner.h",         &Generator::scannerH),
    MapValue("scannerobject",     &Generator::scannerObject),
    MapValue("baseclass",         &Generator::baseClass),
    MapValue("class.h",           &Generator::classH),
    MapValue("class.ih",          &Generator::classIH),
    MapValue("debug",             &Generator::debug),
    MapValue("debugdecl",         &Generator::debugDecl),
    MapValue("debuginit",         &Generator::debugInit),
    MapValue("debugfunctions",    &Generator::debugFunctions),
    MapValue("debugincludes",     &Generator::debugIncludes),
    MapValue("namespace-open",    &Generator::namespaceOpen),
    MapValue("namespace-close",   &Generator::namespaceClose),
    MapValue("namespace-use",     &Generator::namespaceUse),
    MapValue("preincludes",       &Generator::preIncludes),
    MapValue("threading",         &Generator::threading),
    MapValue("tokens",            &Generator::tokens),
    MapValue("LTYPE",             &Generator::ltype),
    MapValue("LTYPEdata",         &Generator::ltypeData),
    MapValue("LTYPEpop",          &Generator::ltypePop),
    MapValue("LTYPEpush",         &Generator::ltypePush),
    MapValue("LTYPEresize",       &Generator::ltypeResize),
    MapValue("LTYPEstack",        &Generator::ltypeStack),
    MapValue("staticdata",        &Generator::staticData),
    MapValue("STYPE",             &Generator::stype),
};

Generator::Map Generator::s_insert(s_mapValues,
                s_mapValues + sizeof(s_mapValues) / sizeof(MapValue));

char const *Generator::s_baseFlag = "\\@";
size_t const Generator::s_baseFlagSize = 2; // backslash and @

