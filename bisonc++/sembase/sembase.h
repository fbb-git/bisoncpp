#ifndef INCLUDED_SEMBASE_
#define INCLUDED_SEMBASE_

#include <iosfwd>
class Block;

class SemBase
{
    public:
        virtual ~SemBase();

        SemBase *clone() const;
        std::string const &str() const;
        bool logic() const;
        size_t size() const;
        Block const &block() const;
        
    protected:
        SemBase() = default;
        SemBase(SemBase const &other) = default;

        void notImplemented() const;

    private:
        virtual SemBase *v_clone() const;
        virtual std::string const &v_str() const;
        virtual bool v_logic() const;
        virtual size_t v_size() const;
        virtual Block const &v_block() const;
};

inline std::string const &SemBase::str() const
{
    return v_str();
}

inline bool SemBase::logic() const
{
    return v_logic();
}

inline size_t SemBase::size() const
{
    return v_size();
}

inline Block const &SemBase::block() const
{
    return v_block();
}

#endif


