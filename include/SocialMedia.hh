#pragma once

#include <string>
#include <vector>

class SocialMedia {
public:
  SocialMedia() = delete;
  SocialMedia(std::string name, std::string address);

  std::string getName() const;
  std::string getAddress() const;

private:
  std::string name;
  std::string address;
};
