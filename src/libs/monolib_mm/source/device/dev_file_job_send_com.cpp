#include "ml/dev_file_job_send_com.h"

#include <string.h>

namespace ml {

DevFileJobSendCom::DevFileJobSendCom(const char *name, WorkObj *parent) : DevFileJob(name, parent) {
  memset(unknown1fc, 0, sizeof(unknown1fc));
  unknown1fc[0] = 'Q';
  unknown1fc[1] = 'f';
  unknown1fc[2] = '9';
  unknown43c[0] = '\0';
  unknown1fc[3] = 'W';
  unknown53c = 0;
  unknown1f9 = true;
}

DevFileJobSendCom::~DevFileJobSendCom() {
  // A body that generates no code still makes the destructor keep its vtable pointer store, which the game's destructors show.
  (void)0;
}
} // namespace ml
