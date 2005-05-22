#ifndef _INCLUDED_ARG_H_
#define _INCLUDED_ARG_H_

/*
        Singleton Class built around getopt() and getopt_long() (3)
*/


#include <string>
#include <getopt.h>
#include <vector>
#include <unistd.h>

namespace FBB
{
    class OptStructArray;
    class Arg
    {
        typedef std::pair<int, std::string>         IntStringPair;
        typedef std::pair<std::string, std::string> StringStringPair;
        typedef struct option                       OptStruct;

        static Arg                      *s_arg;
        static std::string              s_dirsep;

        std::vector<std::string>        d_argv;

        std::vector<IntStringPair >     d_optv;
        std::vector<StringStringPair>   d_longOption;
        std::string                     d_base;

        char const                      **d_argPointer;
        
        public:
            enum Type
            {
                None        = 0,
                Required    = 1,
                Optional    = 2,
                AsCharOption,
            };

            class LongOption
            {
                std::string d_name;
                Arg::Type   d_type;
                int         d_optionChar;
                
                friend class Arg;
                
                public:
                    LongOption(char const *name, Arg::Type type = None);
                    LongOption(char const *name, int optionChar);

                    std::string const &getName() const
                    {
                        return d_name;
                    }
            };


            static Arg &initialize(char const *optstring,
                                    LongOption const * const begin,
                                    LongOption const * const end,
                                    int argc, char **argv);
            static Arg &getInstance();        

            std::string const &basename() const
            {
                return d_base;
            }
            inline unsigned nArgs() const
            {
                return d_argv.size();
            }
            inline unsigned nOptions() const
            {
                return d_optv.size();
            }
            inline unsigned nLongOptions() const
            {
                return d_longOption.size();
            }
            bool option(int option) const
            {
                return findopt(option) != nOptions();
            }
            bool option(std::string const &optchars) const;     // 3
            bool option(std::string *value, int option) const;  // 4
                                                                // 5
            bool option(std::string *value, char const *longOption) const;
    
            char const *operator[](unsigned idx) const;

            void versionHelp(void (*usage)(std::string const &progname), 
                char const *version, unsigned minArgs, int helpFlag = 'h', 
                int versionFlag = 'v') const throw (int);

        private:
            Arg(Arg const &other);                              // NI
            Arg &operator=(Arg const &other);                   // NI

            Arg(char const *optstring, int argc, char **argv);  // 1

            Arg(char const *optstring,                          // 2
                LongOption const * const begin,
                LongOption const * const end,
                int argc, char **argv);


            unsigned findopt(int optchar) const;     
            unsigned findopt(char const *longOption) const;     
            void setBasename(std::string const &argv0);
            void fillLongOptions(
                            OptStruct *optStructs,
                            std::string const &optString,
                            LongOption const * const begin,
                            LongOption const * const end);
            void addLongOption(OptStruct *optStructs,
                            std::string const &optString,
                            LongOption const &longOption);
            int setOptionType(std::string const &optString,
                            LongOption const &longOption);
            bool plainLongOption(int *c, 
                            LongOption const &longOption);
    };

}

#endif
