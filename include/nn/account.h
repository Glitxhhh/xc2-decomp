#pragma once
#include "types.h"

// Follows include/nn/account.h of open-ead/nnheaders (import _ZN2nn7account9CloseUserERKNS0_10UserHandleE).
namespace nn {
namespace account {

class Uid {
public:
  u64 m_Storage[2];
};

class UserHandle {
public:
  Uid m_Uid;
  void *m_Handle;
};

void CloseUser(const UserHandle &handle);

} // namespace account
} // namespace nn
