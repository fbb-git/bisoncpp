#include "production.ih"

void Production::insertAction(Production const *prod, std::ostream &out,
            bool lineDirectives, size_t indent)

{
    if (! prod->hasAction())
        return;

    out <<  setw(indent) << "" << "case " << prod->nr() << ":\n";
    size_t begin = 0;
    Block const &block = prod->action();

    if (lineDirectives)
        out << "#line " << block.lineNr() << " \"" << block.source() <<
                       "\"\n";

    while (true)
    {
        size_t end = block.find_first_of('\n', begin);
        out <<  setw(indent) << "" <<  
                                    block.substr(begin, end - begin) << "\n";
        if (end == string::npos)
            break;
        begin = end + 1;
    }
    out <<  setw(indent) << "" << "break;\n"
           "\n";
}




