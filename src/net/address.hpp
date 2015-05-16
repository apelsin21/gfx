#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <string>
#include <sstream>
#include <cmath>

namespace mg {
    class Address {
        public:
            unsigned short a, b, c, d, port;
            unsigned int host;
            Address(unsigned int, unsigned short);
            Address(const std::string&, unsigned short);
            ~Address();

            std::string getHostAsString();
            void setHost(const std::string&);
            void setHost(unsigned int);
    };
}

#endif //ADDRESS_HPP
