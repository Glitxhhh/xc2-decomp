#pragma once
#include <stddef.h>

#include "ml/dev_file_job.h"
#include "types.h"

namespace ml {

class WorkObj;

class DevFileJobSendCom : public DevFileJob {
public:
  DevFileJobSendCom(const char *name, WorkObj *parent);
  ~DevFileJobSendCom() override;
  void setParam(const char *param);
  void callSendOK(const char *text);
  void callSendError(const char *text);
  bool cancel(FileHandleTh *handle) override;
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  u8 _1fb[0x1fc - 0x1fb];
  char unknown1fc[0x240]; // Inferred role: send packet, starting with a 4 byte signature; original member name unknown.
  char unknown43c[0x100]; // Inferred role: parameter text; original member name unknown.
  s32 unknown53c;         // Inferred role: parameter text length; original member name unknown.
};

static_assert(offsetof(DevFileJobSendCom, unknown1fc) == 0x1fc, "");
static_assert(offsetof(DevFileJobSendCom, unknown43c) == 0x43c, "");
static_assert(offsetof(DevFileJobSendCom, unknown53c) == 0x53c, "");

} // namespace ml
