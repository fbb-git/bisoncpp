#include "production.ih"

void Production::insertAction(Production const *prod, IAContext &context)
{
    if (! prod->hasAction())
        return;

    context.out <<  setw(context.indent) << "" << 
                                    "case " << prod->nr() << ":\n";
    size_t/*unsigned*/ begin = 0;
    Block const &block = prod->action();

    if (context.lineDirectives)
        context.out << "#line " << block.line() << " \"" << context.infile <<
                       "\"\n";

    while (true)
    {
        size_t/*unsigned*/ end = block.find_first_of('\n', begin);
        context.out <<  setw(context.indent) << "" <<  
                                    block.substr(begin, end - begin) << "\n";
        if (end == string::npos)
            break;
        begin = end + 1;
    }
    context.out <<  setw(context.indent) << "" << "break;\n"
           "\n";
}




