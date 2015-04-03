#include "net/address.hpp"

net::Address::Address(unsigned int h, unsigned short p) {
    this->setHost(h);
    this->port = p;
}
net::Address::Address(const std::string& h_string, unsigned short p) {
    this->setHost(h_string);
    this->port = p;
}
net::Address::~Address() {
}

std::string net::Address::getHostAsString() {
    std::stringstream ss;
    ss << this->a
       << "."
       << this->b
       << "."
       << this->c
       << "."
       << this->d;

    return ss.str(); 
}
void net::Address::setHost(const std::string& h_string) {
    std::stringstream s(h_string);

    char ch;
    s >> this->a >> ch >> this->b >> ch >> this->c >> ch >> this->d;

    this->host = (this->a*16777216) + (this->b*65536) + (this->c*256) + (this->d);
}
void net::Address::setHost(unsigned int h) {
    //Convert octets from "ip encoding" to the human readable numbers
    this->a = h & 0xFF;
    this->b = (h >> 8) & 0xFF;
    this->c = (h >> 16) & 0xFF;
    this->d = (h >> 24) & 0xFF;   

    this->host = h;
}
