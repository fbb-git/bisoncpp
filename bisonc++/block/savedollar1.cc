#include "block.ih"

void  Block::saveDollar1(int offset)
{
    string saveText("d_val__ = d_vsp__[");
    saveText += X2a(offset);
    saveText += "];\n";

    insert(0, saveText);
}
