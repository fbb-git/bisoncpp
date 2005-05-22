#include "generator.ih"

Generator::Generator(Rules const &rules, Parser const &parser,
                  ItemSets const &itemSets)
:
    d_rules(rules),
    d_parser(parser),
    d_itemSets(itemSets),
    d_baseclassScope(d_parser.className() + "Base::"),
    d_nameSpace(d_parser.nameSpace()),
    d_debug(d_parser.debugFlag())
{}
