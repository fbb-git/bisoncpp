#include "generator.ih"

void Generator::debugLookup(std::ostream &out) const
{
    if (!d_debug)
        return;

    key(out);

    out << 
        "    if (d_debug__)\n"
        "    {\n"
        "        s_out__ <<  \"lookup(\" << d_state__ << \", \" << "
                                                    "symbol__(d_token__);\n"
        "\n"
        "        if (action < 0)             // a reduction is found\n"
        "            s_out__ << \"): reduce by rule \" << -action;\n"
        "        else if (action == 0)\n"
        "            s_out__ <<  \"): ACCEPT\";\n"
        "        else \n"
        "            s_out__ <<  \"): shift \" << action << \" (\" << "
                                                    "symbol__(d_token__) << \n"
        "                        \" processed)\";\n"
        "\n"
        "        s_out__ << \"\\n\" << dflush__;\n"
        "    }\n";
}
