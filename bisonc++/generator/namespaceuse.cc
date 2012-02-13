#include "generator.ih"

void Generator::namespaceUse(std::ostream &out) const
{
    if (d_nameSpace.empty())
        return;

    key(out);

    out <<  
    "    // UN-comment the next using-declaration if you want to use\n"
    "    // symbols from the namespace " << d_nameSpace << 
                              " without specifying " << d_nameSpace << "::\n"
    "//using namespace " << d_nameSpace << ";\n";
}
