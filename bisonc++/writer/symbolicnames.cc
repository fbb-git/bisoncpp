#include "writer.ih"

void Writer::symbolicNames() const
{
    *d_out <<  
        "typedef std::unordered_map<int, char const *> SMap;\n"
        "typedef SMap::value_type SMapVal;\n"
        "\n"
        "SMapVal s_symArr[] =\n"
        "{\n"
             // Reserved_::UNDETERMINED_ is also used in generator/print.cc
        "    SMapVal(-2, \"Reserved_::UNDETERMINED_\"),  "
                                                    "// predefined symbols\n"
        "    SMapVal(-1, \"Reserved_::EOF_\"),\n"
        "    SMapVal(256, \"errTok_\"),\n"
        "\n";

    for (auto terminal: d_rules.terminals())
        terminalSymbol(terminal, *d_out);

    for (auto nonTerminal: d_rules.nonTerminals())
        nonTerminalSymbol(nonTerminal, *d_out);

    *d_out <<  "};\n"
            "\n"
            "SMap s_symbol\n"
            "(\n"
            "    s_symArr, s_symArr + sizeof(s_symArr) / sizeof(SMapVal)\n"
            ");\n"
            "\n";
}
