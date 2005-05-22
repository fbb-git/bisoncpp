#include "generator.ih"

Generator::MapInsertValue Generator::s_mapValues[] =
{
    MapInsertValue("actioncases",       &Generator::actionCases),
    MapInsertValue("lex",               &Generator::lex),
    MapInsertValue("scanner.h",         &Generator::scannerH),
    MapInsertValue("scannerobject",     &Generator::scannerObject),
    MapInsertValue("baseclass",         &Generator::baseClass),
    MapInsertValue("class.h",           &Generator::classH),
    MapInsertValue("class.ih",          &Generator::classIH),
    MapInsertValue("debug",             &Generator::debug),
    MapInsertValue("debugdecl",         &Generator::debugDecl),
    MapInsertValue("debuginit",         &Generator::debugInit),
    MapInsertValue("debugfunctions",    &Generator::debugFunctions),
    MapInsertValue("debugincludes",     &Generator::debugIncludes),
    MapInsertValue("namespace-open",    &Generator::namespaceOpen),
    MapInsertValue("namespace-close",   &Generator::namespaceClose),
    MapInsertValue("namespace-use",     &Generator::namespaceUse),
    MapInsertValue("preincludes",       &Generator::preIncludes),
    MapInsertValue("tokens",            &Generator::tokens),
    MapInsertValue("LTYPE",             &Generator::ltype),
    MapInsertValue("LTYPEdata",         &Generator::ltypeData),
    MapInsertValue("LTYPEpop",          &Generator::ltypePop),
    MapInsertValue("LTYPEpush",         &Generator::ltypePush),
    MapInsertValue("LTYPEresize",       &Generator::ltypeResize),
    MapInsertValue("LTYPEstack",        &Generator::ltypeStack),
    MapInsertValue("staticdata",        &Generator::staticData),
    MapInsertValue("STYPE",             &Generator::stype),
};

Generator::MapInsert Generator::s_insert(s_mapValues,
                s_mapValues + sizeof(s_mapValues) / sizeof(MapInsertValue));
