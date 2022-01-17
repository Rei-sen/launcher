
#include "SocialMedia.hh"

SocialMedia::SocialMedia(std::string name, std::string address)
    : name(name), address(address) {}

std::string SocialMedia::getAddress() const { return address; }

std::string SocialMedia::getName() const { return name; }
