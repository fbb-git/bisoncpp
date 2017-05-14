#include "generator.ih"

Generator::Generator(Rules const &rules, 
                     unordered_map<string, string> const &polymorphic)
:
    d_arg(Arg::instance()),
    d_rules(rules),
    d_options(Options::instance()),
    d_baseClassScope(d_options.className() + "Base::"),
    d_nameSpace(d_options.nameSpace()),
    d_matchedTextFunction(d_options.scannerMatchedTextFunction()),
    d_tokenFunction(d_options.scannerTokenFunction()),
    d_nameSpacedClassname(d_nameSpace + d_options.className()),
    d_genDebug(d_options.genDebug()),
    d_printTokens(d_options.printTokens()),
    d_threadSafe(d_options.threadSafe()),
    d_polymorphic(polymorphic),

    d_writer(d_baseClassScope, rules)
{}
