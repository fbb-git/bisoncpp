#include "_rulevalue.ih"

namespace std
{
    ostream &operator<<(ostream &out, RuleValue const &t)
    {
        switch (t.tag())
        {
            case RuleValue::CHAR:
            return out << t.asChar();
    
            case RuleValue::INT:
            return out << t.asInt();
    
            default:
            return out << t.asDouble();
        }
    }
}
