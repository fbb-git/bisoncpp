#include "generator.ih"

Generator::Generator(Rules const &rules)
:
    d_arg(Arg::instance()),
    d_rules(rules),
    d_options(Options::instance()),
    d_baseClassScope(d_options.className() + "Base::"),
    d_writer(d_baseClassScope, rules)
{
    d_nameSpace = &d_options.nameSpace();
    d_matchedTextFunction = &d_options.matchedTextFunction();
    d_scannerTokenFunction = &d_options.scannerTokenFunction();
    d_debug = d_options.debug();
    d_print = !d_matchedTextFunction->empty();

//    if (d_matchedTextFunction->empty())
//        d_matchedTextFunction = &s_matchedTextFunction;
//    if (d_scannerTokenFunction->empty())
//        d_scannerTokenFunction = &s_scannerTokenFunction;
}
