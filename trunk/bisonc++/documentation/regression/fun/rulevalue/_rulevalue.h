#ifndef _INCLUDED_RULEVALUE_
#define _INCLUDED_RULEVALUE_

#include <vector>
#include <iosfwd>

class RuleValue
{
    public:
        typedef std::vector<RuleValue>  Args;

        struct Function
        {
            enum Type
            {
                DOUBLE_IN_DOUBLE_OUT,
                DOUBLE_IN_RAD_OUT,      // fun expects double, returns radians
                RAD_IN_DOUBLE_OUT,      // fun expects radians, returns double
            };
    
            union Ptr
            {
                double (*unary)(double); 
                double (*binary)(double, double);
            };
    
            Type d_type;
            Ptr  d_ptr;
            size_t d_arity;
    
            Function(double (*)(double), Type t = DOUBLE_IN_DOUBLE_OUT);
            Function(double (*)(double, double));

            size_t arity() const;
            double (*unary() const)(double); 
            double (*binary() const)(double, double);
            double value() const;
            Type type() const;
        };

    private:
        union ValueUnion
        {
            char    c;
            int     i;
            double  d;
            size_t  s;
            Function const *f;
            Args    *args;
        };

        static char const *s_tagName[];

    public:
        enum ValueTag                   // modify data.cc if this changes
        {
            ERROR,                      // something failed.
            CHAR,
            INT,
            DOUBLE,
            VARIABLE,
            FUNCTION,
            ARG_VECTOR,
        };

    private:
        ValueTag  d_tag;
        ValueUnion d_value;

    public:        
        RuleValue();
        RuleValue(char c);
        RuleValue(int i);
        RuleValue(double d);
        RuleValue(unsigned idx);
        RuleValue(Function const &funRef);
        RuleValue(Args *args);
        RuleValue(char const *ident);
        RuleValue(RuleValue const &other);

        ~RuleValue();

        ValueTag tag() const;
        char const *tagName() const;

        char asChar() const;
        int asInt() const;
        double asDouble() const;

        Function const &fun() const;
        size_t varIdx() const;

        RuleValue operator-() const;
        RuleValue operator~() const;

        RuleValue &operator=(RuleValue const &other);

        RuleValue &operator+=(RuleValue const &other);
        RuleValue &operator-=(RuleValue const &other);
        RuleValue &operator*=(RuleValue const &other);
        RuleValue &operator/=(RuleValue const &other);
        RuleValue &operator%=(RuleValue const &other);
        RuleValue &operator&=(RuleValue const &other);
        RuleValue &operator^=(RuleValue const &other);
        RuleValue &operator|=(RuleValue const &other);
        RuleValue &operator<<=(RuleValue const &other);
        RuleValue &operator>>=(RuleValue const &other);

        RuleValue const &operator[](size_t idx) const;
        size_t size() const;

        RuleValue &push_arg(RuleValue const &other);

    private:
        void destroy();
        void copy(RuleValue const &other);
};

inline RuleValue::RuleValue(RuleValue const &other)
{
    copy(other);
}

inline RuleValue::~RuleValue()
{
    destroy();
}

inline void RuleValue::destroy()
{
    if (d_tag == ARG_VECTOR)
        delete d_value.args;
}

inline RuleValue const &RuleValue::operator[](size_t idx) const
{
    return (*d_value.args)[idx];
}

inline RuleValue RuleValue::operator~() const
{
    return RuleValue(~asInt());
}

inline RuleValue::ValueTag RuleValue::tag() const
{
    return d_tag;
}

inline char const *RuleValue::tagName() const
{
    return s_tagName[d_tag];
}

inline size_t RuleValue::size() const
{
    return d_value.args->size();
}

inline size_t RuleValue::Function::arity() const
{
    return d_arity;
}

inline RuleValue::Function::Type RuleValue::Function::type() const
{
    return d_type;
}

inline double (*RuleValue::Function::unary() const)(double)
{
    return d_ptr.unary;
}

inline double (*RuleValue::Function::binary() const)(double, double)
{
    return d_ptr.binary;
}

inline RuleValue &RuleValue::push_arg(RuleValue const &value)
{
    d_value.args->push_back(value);
    return *this;
}

inline size_t RuleValue::varIdx() const
{
    return d_value.s;
}

namespace std
{
    ostream &operator<<(ostream &out, RuleValue const &t);
}
    
#endif




