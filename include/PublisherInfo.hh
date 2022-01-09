
#pragma once

#include "UserInfo.hh"

class PublisherInfo : public UserInfo {
public:
  using UserInfo::UserInfo;

  bool hasPublisherAccess() const override;
};
