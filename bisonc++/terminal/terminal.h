#ifndef _INCLUDED_TERMINAL_
#define _INCLUDED_TERMINAL_

#include <string>
#include <vector>
#include <set>
#include <limits>

#include "../symbol/symbol.h"

class Terminal: public Symbol
{
    public:
        typedef std::vector<Terminal *>         Vector;
        typedef std::vector<Terminal const *>   ConstVector;
        typedef ConstVector::const_iterator     ConstIter;

        enum
        {
            INITIAL_SYMBOLIC_VALUE = 257,   // See rules/data.cc for Terminals
                                        // defined by default.

            DEFAULT = std::numeric_limits<size_t>::max()
                                        // results in the next symbolic
                                        // terminal value to be assigned.
        };
        enum Association                // adapt s_association[] in data.cc 
        {                               // when this changes
            UNDEFINED,
            NONASSOC,
            LEFT,
            RIGHT,
        };
        enum Precedence                 // returned by comparePrecedence()
        {                               
            SMALLER = -1,
            EQUAL   = 0,
            LARGER  = 1,
        };

    private:
        size_t d_value;                 // value assigned to the symbol

        Association d_association;      // association type of the symbol
        size_t d_precedence;            // precedence value of the symbol
                                        
        std::string d_literal;          // literal text value of a
                                        // symbol.
        std::string d_readableLiteral;  // with character terminals this
                                        // contains a quoted character, maybe
                                        // escaped as in '\n'

        FirstSet d_firstSet;            // set of symbols that can be seen at
                                        // this terminal symbol. It only
                                        // contains the current terminal
                                        // symbol, but is returned by
                                        // Element::firstSet() through the
                                        // virtual v_firstSet() function below

        static std::set<size_t> s_valueSet; // all terminal token values
        static size_t s_precedence;         // last-used precedence so far
        static char const *s_association[]; // array of literal association
                                            // names 
        static size_t s_value;              // value assigned, unless 
                                            // explictly defined
        static size_t s_maxValue;           // maximum assigned terminal value

        static std::ostream &(Terminal::*s_insertPtr)(std::ostream &out) 
                                                                        const;
                                        // pointer to the insertion function
                                        // to use.
    public:
        Terminal(std::string const &name, 
                    Type type,
                    size_t value = DEFAULT, 
                    Association association = UNDEFINED, 
                    std::string const &stype = ""); 
                                    // stype: type assigned by 
                                    // explicit symbol type association, 
                                    // e.g. %type <int> symbol

        Terminal(std::string const &name,       // used for reserved terminals
                std::string const &literal,
                    Type type);

        virtual ~Terminal();

        Association association() const;

        Precedence comparePrecedence(Terminal const *other) const;
        size_t precedence() const;
        void setLiteral(std::string const &literal);
        void setValue(size_t value);  // reassign a token value
        void setPrecedence(size_t value);

        static Terminal *downcast(Symbol *sp);
        static Terminal const *downcast(Element const *sp);
                                            // used with Element by Writer

        static bool compareValues(Terminal const *left, Terminal const *right);
        static Precedence comparePrecedence(Symbol const *first,
                                                      Symbol const *second);

        static void incrementPrecedence();
        static void resetPrecedence();     // see Parser::parseDeclarations()
        static size_t sPrecedence();
        static void set_sPrecedence(size_t prec);

        static bool setUnique(size_t value);    // true if unique
        static void unused(Terminal const *terminal);
        static size_t maxValue();

        static void inserter(std::ostream &(Terminal::*insertPtr)
                                            (std::ostream &out) const);

                                    // Symbolic as name, chars as 
                                    // quoted chars
        std::ostream &plainName(std::ostream &out) const;

                                    // Symbolic as quoted names, 
                                    // chars as char consts
        std::ostream &quotedName(std::ostream &out) const;

                                    // Value followed by quoted name
        std::ostream &valueQuotedName(std::ostream &out) const;

                                    // Values or names (of reserved tokens)
        std::ostream &nameOrValue(std::ostream &out) const;

    private:
        virtual FirstSet const &v_firstSet() const;
        virtual size_t v_value() const;
        virtual std::ostream &insert(std::ostream &out) const;
};

inline std::ostream &operator<<(std::ostream &out, 
          std::ostream &(Terminal::*insertPtr)(std::ostream &out) const)
{
    Terminal::inserter(insertPtr);
    return out;
}

inline std::ostream &Terminal::plainName(std::ostream &out) const
{
    return out << d_readableLiteral;
}

inline Terminal *Terminal::downcast(Symbol *sp)
{
    return dynamic_cast<Terminal *>(sp);
}

inline Terminal const *Terminal::downcast(Element const *sp)
{
    return dynamic_cast<Terminal const *>(sp);
}

inline void Terminal::incrementPrecedence()
{
    ++s_precedence;
}

inline void Terminal::resetPrecedence()     // see Parser::parseDeclarations()
{
    s_precedence = 0;
}

inline size_t Terminal::maxValue()
{
    return s_maxValue;
}

inline Terminal::Association Terminal::association() const
{
    return d_association;
}

inline Terminal::Precedence Terminal::comparePrecedence(
                                                Terminal const *other) const
{
    return 
        d_precedence > other->d_precedence ? LARGER  :
        d_precedence < other->d_precedence ? SMALLER :
                                         EQUAL;
}            

inline size_t Terminal::precedence() const
{
    return d_precedence;
}

inline size_t Terminal::v_value() const
{
    return d_value;
}

inline FirstSet const &Terminal::v_firstSet() const
{
    return d_firstSet;
}        

inline void Terminal::setLiteral(std::string const &literal)
{
    d_literal = literal;
}

inline void Terminal::setPrecedence(size_t value)
{
    d_precedence = value;
}

inline size_t Terminal::sPrecedence()
{
    return s_precedence;
}

inline void Terminal::set_sPrecedence(size_t prec)
{
    s_precedence = prec;
}

inline bool Terminal::compareValues(Terminal const *left, 
                                    Terminal const *right)
{
    return left->d_value < right->d_value;
}

inline std::ostream &Terminal::insert(std::ostream &out) const
{
    return (this->*Terminal::s_insertPtr)(out);
}

inline void Terminal::inserter(std::ostream &(Terminal::*insertPtr)
                                             (std::ostream &out) const)
{
    s_insertPtr = insertPtr;
}

// operator<< is already available through Element

#endif



