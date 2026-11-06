#include "ml/proc_exception.h"

#include "window/window.h"

namespace ml {

void ProcException::setInfo(EXCEPTION_PRIO prio) { unknown228 = prio; }

void ProcException::setInfo(u32 wid, const wchar_t *message) {
  unknown1f8 = wid;
  unknown200 = message;
}

bool ProcException::isCheckOK() const { return unknown20c == 0.8f; }

void ProcException::forceShutdown() {
  unknown224 = true;
  wkSetEvent(static_cast<EVT>(0));
}

void ProcException::renderWide(const wchar_t *message) {}

void ProcException::fatal(const wchar_t *message) {}

void ProcException::entry(IException *exception) { unknown004.unknown38[unknown004.unknown00++] = exception; }

void ProcException::remove(IException *exception) {
  for (int i = 0; i < unknown004.unknown00; i++) {
    if (unknown004.unknown38[i] == exception) {
      for (int j = i; j < unknown004.unknown00 - 1; j++) {
        unknown004.unknown38[j] = unknown004.unknown38[j + 1];
      }
      unknown004.unknown00--;
      return;
    }
  }
}

void ProcException::setMessage(const wchar_t *message) {
  if (get() != nullptr) {
    get()->unknown200 = message;
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcException>::~PtrSingleton();
