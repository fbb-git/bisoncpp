#ifndef _INCLUDED_SHIFTREDUCE_
#define _INCLUDED_SHIFTREDUCE_

class Production;

class ShiftReduce
{
    union
    {
        unsigned d_state;
        Production const *d_production;
    };

    unsigned d_status;
        
    public:
        enum Status
        {
            ACCEPT      = (1 << 0),
            SHIFT       = (1 << 1),
            REDUCE      = (1 << 2),
            REPORTED    = (1 << 3)
        };

        ShiftReduce(Production const *production)
        :
            d_production(production),
            d_status(REDUCE)
        {}
        ShiftReduce(unsigned nextState)
        :
            d_state(nextState),
            d_status(SHIFT)
        {}
        ShiftReduce(Status accept)
        :
            d_state(0),
            d_status(ACCEPT)
        {}
        bool accept() const
        {
            return d_status & ACCEPT;
        }
        bool acceptOrReduce() const
        {
            return d_status & (ACCEPT | REDUCE);
        }
        Production const *production() const
        {
            return d_production;
        }
        bool reported() const
        {
            return d_status & REPORTED;
        }
        void setProduction(Production const *production)
        {
            d_production = production;
        }
        bool shift() const
        {
            return d_status & SHIFT;
        }
        unsigned state() const
        {
            return d_state;
        }
        void setReported()
        {
            d_status |= REPORTED;
        }
        void setState(unsigned nextState)
        {
            d_state = nextState;
            d_status = SHIFT;
        }
        bool operator==(Production const *pp) const;
};

        
#endif
